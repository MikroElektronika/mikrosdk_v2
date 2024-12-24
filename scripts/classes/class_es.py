import re, time
from elasticsearch import Elasticsearch
from enum import Enum

class index():
    class Status(Enum):
        SUCCESS = 200
        ERROR = 404

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
    def init(es_host, es_user, es_password, retry=None):
        retry_check = 10
        if retry:
            retry_check = retry
        num_of_retries = 1
        while True:
            print(f"Trying to connect to ES. Connection retry:  {num_of_retries}")
            es = Elasticsearch([es_host], http_auth=(es_user, es_password))
            if es.ping():
                break
            # Wait for 1 second and try again if connection fails
            if retry_check == num_of_retries:
                # Exit if it fails 10 times, something is wrong with the server
                raise ValueError("Connection to ES failed!")
            num_of_retries += 1
            es = None

            time.sleep(1)

        return es

    @staticmethod
    def response(es: Elasticsearch, index, query_size=5000):
        # Search query to use
        query_search = {
            "size": query_size,
            "query": {
                "match_all": {}
            }
        }

        # Search the base with provided query
        num_of_retries = 1
        while num_of_retries <= 10:
            try:
                response = es.search(index=index, body=query_search)
                if not response['timed_out']:
                    break
            except:
                print("Executing search query - retry number %i" % num_of_retries)
            num_of_retries += 1

        return response

    @staticmethod
    def find_item(items, check):
        for index in items:
            if 'name' in index:
                if index['name'] == check:
                    return True
        return False

    @staticmethod
    def api_index(es: Elasticsearch, doc_index, doc_type, doc_id, doc_body):
        return es.index(
            index=doc_index,
            doc_type=doc_type,
            id=doc_id,
            body=doc_body
        )

    def __init__(self, es_host, es_user, es_password, index, token, retry=None):
        self.es_instance = self.init(es_host, es_user, es_password, retry)
        self.index = index
        self.token = token
        self.indexed_items = []

    def fetch(self, regex=r'.+', query_size=5000):
        pattern = re.compile(regex)
        response = self.response(self.es_instance, self.index, query_size)

        for eachHit in response['hits']['hits']:
            if 'name' in eachHit['_source']:
                if pattern.match(eachHit['_source']['name']):
                    self.indexed_items.append(
                        {
                            'doc': {
                                'index': eachHit['_index'],
                                'type': eachHit['_type'],
                                'id': eachHit['_id']
                            },
                            'source': eachHit['_source']
                        }
                    )

    def exists(self, check, query_size=5000):
        ## Did not use ES exists function as it requires doc_type and doc_id
        ## For future use it is better to search by name only
        response = self.response(self.es_instance, self.index, query_size)
        return self.find_item([index['_source'] for index in response['hits']['hits']], check)

    def create(self, doc_type, doc_id, doc_body):
        response = self.api_index(self.es_instance, self.index, doc_type, doc_id, doc_body)
        if not 'created' == response['result']:
            raise ValueError("%s%s failed to index to %s!" % (self.Colors.FAIL, doc_id, self.index))
        else:
            print("%sINFO: Asset \"%s\" created. - %s" % (self.Colors.OKGREEN, doc_body['name'], doc_body['download_link']))

    def update(self, doc_type, doc_id, doc_body):
        response = self.api_index(self.es_instance, self.index, doc_type, doc_id, doc_body)
        if doc_type:
            if response['created'] and 'created' == response['result']:
                print("%sWARNING: Asset \"%s\" created instead of updating. - %s" % (self.Colors.WARNING, doc_body['name'], doc_body['download_link']))
            elif not 'updated' == response['result']:
                raise ValueError("%s%s failed to update on %s!" % (self.Colors.FAIL, doc_id, self.index))
            else:
                print("%sINFO: Asset \"%s\" updated. - %s" % (self.Colors.OKGREEN, doc_body['name'], doc_body['download_link']))
        # For new DBP elasticsearch there is no 'created' field in response, so we just check 'result'
        else:
            if 'created' == response['result']:
                print("%sWARNING: Asset \"%s\" created instead of updating. - %s" % (self.Colors.WARNING, doc_body['name'], doc_body['download_link']))
            elif not 'updated' == response['result']:
                raise ValueError("%s%s failed to update on %s!" % (self.Colors.FAIL, doc_id, self.index))
            else:
                print("%sINFO: Asset \"%s\" updated. - %s" % (self.Colors.OKGREEN, doc_body['name'], doc_body['download_link']))

    def delete(self, doc_type, doc_id):
        response = self.es_instance.delete(
            index=self.index,
            doc_type=doc_type,
            id=doc_id
        )
        if not 'deleted' == response['result']:
            raise ValueError("%s%s failed to delete from %s!" % (self.Colors.FAIL, doc_id, self.index))
        else:
            print("%sINFO: Asset \"%s\" deleted." % (self.Colors.OKGREEN, doc_id))
