import urllib.request, urllib.error, urllib.parse
import json
import math
import requests

class Read_Weather:

    def read_address(self, address):
        """ a function that takes a one line address and return the latitude and longitude
            of that address
        """
    
        geocoding_api = 'https://geocoding.geo.census.gov/geocoder/locations/onelineaddress?'
        parms = dict()
        parms['address'], parms['benchmark'], parms['format'] = address, 'Public_AR_Current', 'json'
    
        try:
            url = geocoding_api + urllib.parse.urlencode(parms)
    
        except ValueError:
            print(f"The website you entered ({address}) has to start with http://")  # if the user entered a wrong website
        except urllib.error.HTTPError:
            print(f"HTTP Error 404: {address} Not Found")
        else:
            print('Retrieving', url)
            uh = urllib.request.urlopen(url)
            data = uh.read().decode()
    
            try:
                js = json.loads(data)
            except:
                print('==== Failure To Retrieve ====')
                print(data)
                exit()
    
            coordinates = dict()
    
            try:
                coordinates['x'] = js['result']['addressMatches'][0]['coordinates']['x']
                coordinates['y'] = js['result']['addressMatches'][0]['coordinates']['y']
    
            except IndexError as i:
                print(i, '\nplease, make sure that you enter your one-line address correctly')
    
            return coordinates
    
    
    def distance(self,user_address_1, user_address_2):
        """ a function that return the distance in miles """
    
        x1, y1 = user_address_1['x'], user_address_1['y']
        x2, y2 = user_address_2['x'], user_address_2['y']
    
        radius = 3956
    
        dx = math.radians(x2 - x1)
        dy = math.radians(y2 - y1)
    
        a = math.sin(dx / 2) * math.sin(dx / 2) + math.cos(math.radians(x1)) \
            * math.cos(math.radians(x2)) * math.sin(dy / 2) * math.sin(dy / 2)
    
        c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    
        d = radius * c
    
        return d
    
    
    def the_weather(self, user_weather_1, user_weather_2):
        """ a function to retrieve the current temperature of both addresses using the OpenWeatherMap API"""
    
        x1, y1 = user_weather_1['y'], user_weather_1['x']
        x2, y2 = user_weather_2['y'], user_weather_2['x']
    
        api_key = "7a160b5068bd8bad7f789b5e9b450a69"
        url_1 = "https://api.openweathermap.org/data/2.5/onecall?lat=%s&lon=%s&appid=%s&units=metric" % (x1, y1, api_key)
        url_2 = "https://api.openweathermap.org/data/2.5/onecall?lat=%s&lon=%s&appid=%s&units=metric" % (x2, y2, api_key)
    
        response_1 = requests.get(url_1)
        response_2 = requests.get(url_2)
    
        data_1 = json.loads(response_1.text)
        data_2 = json.loads(response_2.text)
    
        current_temp_1 = data_1["current"]["temp"]
        current_temp_2 = data_2["current"]["temp"]
    
        return current_temp_1, current_temp_2
    
    
    def main_1(self):
        address_1 = input('Enter the first address (must be a one line address): ')
        address_2 = input('Enter the second address (must be a one line address): ')
    
        user_address_1 = self.read_address(address_1)
        user_address_2 = self.read_address(address_2)
    
        user_weather_1 = user_address_1
        user_weather_2 = user_address_2
    
        the_distance = round(self.distance(user_address_1, user_address_2))
    
        weather_1, weather_2 = self.the_weather(user_weather_1, user_weather_2)
    
        #print(f"The distance between the two addresses is about {the_distance} miles")
        #print(f"the weather for the first address is {weather_1} degree Celsius")
        #print(f"the weather for the second address is {weather_2} degree Celsius")
        #print(weather_1)
        #print(weather_2)
        return weather_1, weather_2, the_distance
