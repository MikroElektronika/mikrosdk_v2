import os, argparse
import classes.class_release_calendar as calendar
import classes.class_generate_events_json as calendar_events

from datetime import timedelta

if __name__ == "__main__":
    ## Set up argument parsing
    parser = argparse.ArgumentParser(description="Iterate through dates in a range and create calendar events if needed.")
    parser.add_argument("api_key", help="Teamup API key - secret.")
    parser.add_argument("title", help="Event title for calendar.")
    parser.add_argument("calendar_name", help="Calendar name to edit data for.")
    parser.add_argument("calendar_id", help="Calendar ID to edit data for.")
    parser.add_argument("doc_link", help="Spreadsheet table with release details - link.")
    parser.add_argument("--force_mikroe_calendar", type=bool, default=True, help="If set to true, calendar name value MUST match existing name.")
    parser.add_argument("--start_date", help="Optional start date in the format YYYY-MM-DD. Defaults to the current date if not provided.")
    parser.add_argument("--end_date", help="Optional end date in the format YYYY-MM-DD. If not provided, 3 weeks will be added to the start date.")
    parser.add_argument("--force_update", action='store_true', help="Optional parameter used to force update of existing event. False by default.")

    ## Parse the arguments
    args = parser.parse_args()

    ## Update release calendar values
    release_calendar = calendar_events.events_json(args.doc_link, args.title)
    release_calendar.fetch_data()
    ## Then generate the input file for teamup API
    release_calendar.generate_file(os.path.join(os.path.dirname(__file__), 'releases.json'))

    ## Instantiate the class
    ## If start date not passed, will take current date on script run
    ## If end_date not passed, will take current date on script run + 3 weeks
    ## If specific dates are needed, pass them as ISO date strings:
    ## i.e.
    # --start_date "2024-09-11" --> September 11th
    # --end_date "2024-09-15" --> September 15th
    release_calendar = calendar.ReleaseCalendar(
        args.api_key, args.title,
        os.path.join(os.path.dirname(__file__), 'releases.json'),
        args.force_mikroe_calendar,
        args.calendar_name, args.calendar_id,
        args.start_date, args.end_date
    )

    ## Fetch all events within the specified date range
    release_calendar.fetch_events()

    ## Load the new events from the provided JSON file
    release_calendar.fetch_events_from_json()

    ## Fetch the appropriate subcalendar from the calendar
    release_calendar.fetch_subcalendars()

    ## Iterate through the date range and create/update events
    current_date = release_calendar.start_date
    while current_date <= release_calendar.end_date:
        ## Check for provided JSON file for release
        print("Checking events for %s..." % current_date.strftime('%Y-%m-%d'))

        ## Check if the event already exists
        event_exists = False
        for each_event in release_calendar.calendar['events']:
            if each_event['start_dt'].startswith(current_date.strftime('%Y-%m-%d')):
                if (release_calendar.title.lower() == each_event['title'].lower()):
                    event_exists = True
                    break

        ## If event doesn't exist, create it
        if not event_exists:
            release_calendar.create_event(
                release_calendar.fetch_matching_events(current_date.strftime('%Y-%m-%d'))
            )
        ## If event exists and the force flag is provided, update it
        elif event_exists and args.force_update:
            release_calendar.update_event(
                release_calendar.fetch_matching_events(current_date.strftime('%Y-%m-%d')),
                each_event
            )

        ## Move to the next day
        current_date += timedelta(days=1)
