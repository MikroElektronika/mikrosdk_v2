## IMPORT SECTION
import os
import json
import requests

from enum import Enum
from datetime import datetime, timedelta

## CODE SECTION
class ReleaseCalendar:
    class RequestRetVal(Enum):
        '''Enum for response statuses that represent success values for creating and updating events'''
        CREATE_SUCCESS = 201
        UPDATE_SUCCESS = 200

    @staticmethod
    def fetch_dynamic_event_types():
        '''Simulate fetching event types dynamically. You can replace this with an API call if necessary'''
        return {
            "Blog" : "Blog",
            "Newsletter" : "Newsletter",
            "Offer" : "Offer",
            "Product - InMaking" : "Product - InMaking",
            "Product - Ready" : "Product - Ready",
            "Product - Text Ready" : "Product - Text Ready",
            "Product - Update" : "Product - Update",
            "Website" : "Website",
            "Test Calendar" : "Test Calendar" ## Left in for testing purposes
        }

    @staticmethod
    def create_dynamic_enum(name, dynamic_values):
        '''Dynamically create an Enum class for event types'''
        return Enum(name, dynamic_values)

    def __init__(self, key, title, event_json_path, implement_check, calendar_name, calendar_id, start_date_str=None, end_date_str=None):
        '''Initialize the class with API credentials and calendar information'''
        self.api_key = key  ## Fetch the API key
        self.calendar_id = calendar_id  ## Fetch the calendar ID

        ## If set to true will enforce strict calendar name checks
        self.implement_check = implement_check

        ## Event title
        self.title = title

        ## Calendar name
        self.calendar_name = calendar_name

        ## Path to the JSON file containing event details
        self.event_json_path = event_json_path

        ## Create dynamic enum for event types
        self.EventType = self.create_dynamic_enum('EventType', self.fetch_dynamic_event_types())
        if self.implement_check:
            if calendar_name not in self.EventType:
                raise ValueError('%s not found in predefined calendars.' % calendar_name)

        ## If no start date is provided, use the current date
        if start_date_str:
            self.start_date = datetime.strptime(start_date_str, '%Y-%m-%d')
        else:
            self.start_date = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)  # Set time to midnight

        ## If no end date is provided, add 3 weeks to the start date
        if end_date_str:
            self.end_date = datetime.strptime(end_date_str, '%Y-%m-%d')
        else:
            self.end_date = self.start_date + timedelta(weeks=3)

    def fetch_subcalendars(self):
        '''Fetch subcalendars based on the provided calendar name'''
        url = f"https://api.teamup.com/{self.calendar_id}/subcalendars"
        headers = {"Teamup-Token": self.api_key}

        ## Make a GET request to retrieve subcalendar information
        response = requests.get(url, headers=headers)
        if response.status_code == self.RequestRetVal.UPDATE_SUCCESS.value:
            ## Filter the subcalendar by name and store it in the class
            if self.implement_check:
                self.subcalendars = [
                    calendar for calendar in response.json()['subcalendars']
                    if calendar["name"] == self.EventType[self.calendar_name].value
                ]
            else:
                self.subcalendars = [
                    calendar for calendar in response.json()['subcalendars']
                    if calendar["name"] == self.calendar_name
                ]
            print(json.dumps(self.subcalendars, indent=4))  ## Display all sub-calendars with their IDs
            return self.subcalendars
        else:
            print(f"Failed to retrieve subcalendars. Status code: {response.status_code}, Response: {response.text}")
            return None

    def fetch_events(self):
        '''Fetch events for the specified date range'''
        url = f"https://api.teamup.com/{self.calendar_id}/events?startDate={self.start_date.strftime('%Y-%m-%d')}&endDate={self.end_date.strftime('%Y-%m-%d')}"

        # Headers for the request
        headers = {
            "Teamup-Token": self.api_key
        }

        ## Make a GET request to get sub-calendar information
        response = requests.get(url, headers=headers)

        if response.status_code == 200:
            self.calendar = response.json()  ## Store the fetched calendar events
            print(json.dumps(self.calendar, indent=4))  ## Pretty-print the calendar information
        else:
            print(f"Failed to retrieve calendars. Status code: {response.status_code}, Response: {response.text}")

    def fetch_events_from_json(self):
        '''Load events from the provided JSON file'''
        if os.path.exists(self.event_json_path):
            if os.path.isfile(self.event_json_path):
                with open(self.event_json_path, 'r') as file:
                    self.events = json.load(file)
                if not self.title in self.events:
                    raise ValueError('Provided json has no events for %s.' % self.title)
                return
        raise ValueError('Provided wrong path for event json file.')

    def fetch_matching_events(self, current_date):
        '''Fetch events with start_dt matching the current date'''
        return [
            event for event in self.events[self.title]["events"]
            if event["start_dt"].startswith(current_date)
        ]

    def create_event(self, events):
        '''Create new events in the Teamup calendar'''
        url = f"https://api.teamup.com/{self.calendar_id}/events"
        headers ={
            "Teamup-Token": self.api_key,
            "Content-Type": "application/json"
        }

        for each_event in events:
            ## Update the event with the relevant subcalendar IDs
            each_event.update({"subcalendar_ids": [subcalendar['id'] for subcalendar in self.subcalendars]})
            ## Make a POST request to add the event
            response = requests.post(url, headers=headers, data=json.dumps(each_event))

            ## Check the response
            if response.status_code == self.RequestRetVal.CREATE_SUCCESS.value:
                print("Event created successfully!")
            else:
                print(f"Failed to create event. Status code: {response.status_code}, Response: {response.text}")

    def update_event(self, events, event_to_update):
        '''Update existing events in the calendar'''
        headers ={
            "Teamup-Token": self.api_key,
            "Content-Type": "application/json"
        }

        for each_event in events:
            ## Update only if title is the same and date is the same
            if (event_to_update['title'] == each_event['title']) and \
               (event_to_update['start_dt'] == each_event['start_dt']):

                ## Iterate all keys and fetch new values
                for each_key in event_to_update:
                    if each_key in each_event:
                        event_to_update[each_key] = each_event[each_key]

                ## Create the specific event URL
                url = f"https://api.teamup.com/{self.calendar_id}/events/{event_to_update['id']}"

                ## Make a POST request to add the event
                response = requests.put(url, headers=headers, data=json.dumps(event_to_update))

                ## Check the response
                if response.status_code == self.RequestRetVal.UPDATE_SUCCESS.value:
                    print("Event updated successfully!")
                else:
                    print(f"Failed to update event. Status code: {response.status_code}, Response: {response.text}")
