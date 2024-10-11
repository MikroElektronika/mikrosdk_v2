import  requests
from enum import Enum

class repo():
    class Status(Enum):
        SUCCESS = 200

    class Colors:
        HEADER = '\033[95m'
        OKBLUE = '\033[94m'
        OKCYAN = '\033[96m'
        OKGREEN = '\033[92m'
        WARNING = '\033[93m'
        FAIL = '\033[91m'
        ENDC = '\033[0m'
        BOLD = '\033[1m'
        UNDERLINE = '\033[4m'

    @staticmethod
    def fetch_all_assets(url, token):
        headers = {
            'Authorization': f'token {token}'
        }

        asset_list = []

        response = requests.get(url, headers=headers)
        response.raise_for_status()
        assets = response.json()

        # If no more assets, break out of loop
        if not assets:
            return None

        for asset in assets.get('assets', []):
            asset_list.append(asset)

        return asset_list

    @staticmethod
    def fetch_asset(assets, asset_name, loose=False):
        for asset in assets:
            if loose:
                if asset_name in asset['name']:
                    return asset
            else:
                if asset['name'] == asset_name:
                    return asset
        return None

    def __init__(self, repo, token, release_id='latest'):
        self.repo = repo
        self.token = token
        if 'latest' == release_id:
            self.repo_url = f'https://api.github.com/repos/{repo}/releases/latest'
        else:
            self.repo_url = f'https://api.github.com/repos/{repo}/releases/{release_id}/assets'
        self.assets = self.fetch_all_assets(self.repo_url, self.token)

    def asset_exists(self, asset_name, loose=False):
        ## TODO - implement asset checking in the future
        return

    def asset_fetch_url_api(self, asset_name, loose=False):
        asset = self.fetch_asset(self.assets, asset_name, loose)
        if asset:
            return asset['url']
        return None

    def asset_fetch_url_browser(self, asset_name, loose=False):
        asset = self.fetch_asset(self.assets, asset_name, loose)
        if asset:
            return asset['browser_download_url']
        return None

    def asset_upload(self, asset_path, asset_name):
        ## TODO - implement asset upload in the future
        return

    def asset_delete(self, asset_path, asset_name):
        ## TODO - implement asset deletion in the future
        return
