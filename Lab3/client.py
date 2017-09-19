from suds.client import Client as SudsClient
import requests

url_arithmetic = 'http://127.0.0.1:5000/soap/ArithmeticService?wsdl'
url_trignometric = 'http://127.0.0.1:5000/soap/TrignometricService?wsdl'

client = SudsClient(url=url_arithmetic, cache=None)
r = client.service.add(first_ = 2, second_ = 3)
print(r)

r = client.service.subtract(first_ = 15, second_ = 4)
print(r)

client = SudsClient(url=url_trignometric, cache=None)

r = client.service.sine(90)
print(r)

r = client.service.cosine(90)
print(r)
