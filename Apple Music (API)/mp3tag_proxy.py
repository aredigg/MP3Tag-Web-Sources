# Apple Music proxy for Apple Music Web Source 4.0 for MP3Tag
# Version 1.0b2 © 2023
# All Rights Reserved

from http.server import BaseHTTPRequestHandler, HTTPServer
from ssl import wrap_socket
import requests

TOKEN = "Bearer eyJhbGciOiJFUzI1NiIsInR5cCI6IkpXVCIsImtpZCI6IldlYlBsYXlLaWQifQ.eyJpc3MiOiJBTVBXZWJQbGF5IiwiaWF0IjoxNjkyNjM5MTM1LCJleHAiOjE2OTk4OTY3MzUsInJvb3RfaHR0cHNfb3JpZ2luIjpbImFwcGxlLmNvbSJdfQ.nJ_cqCk2lRPbzK7jxHXwu1aGaxGiMYa0px0DdAfI_9GcUuB5Ki_lKO6IfWEgxA5Dr9_KAh81ACpHkcgXjh8ArQ"
USER = ""
URL = "https://amp-api.music.apple.com"
PORT = 8084

session = requests.Session()

session.headers.update(
		{
				"User-Agent": "Mozilla/5.0 (Proxy 1.0)",
				"Accept": "application/json",
				"Authorization": TOKEN,
				"media-user-token": USER,
				"Content-Type": "application/json",
				"Connection": "keep-alive",
				"Origin": "https://music.apple.com"
		}
)

class request_handler(BaseHTTPRequestHandler):

	def do_GET(self):
		request_url = URL + self.path
		date = self.date_time_string(timestamp=None)
		print(f"{date} {request_url}")
		response = session.get(request_url)
		self.send_response(response.status_code)
		if response.status_code != 200:
			print(f" -- ERROR -- {response.status_code}")
			self.send_header('Content-type', 'application/json')
		else:
			print(f" -- OK --")
			self.send_header('Content-type', 'application/json')
		self.end_headers()
		self.wfile.write(response.content)
		
	def do_HEAD(self):
		print("HEAD")
		
	def do_POST(self):
		print("POST")
		
	def do_SPAM(self):
		print("SPAM")

server = HTTPServer(('', PORT), request_handler)
server.socket = wrap_socket(server.socket, certfile="certificate.pem", keyfile="private-key.pem", server_side=True)
server.serve_forever()