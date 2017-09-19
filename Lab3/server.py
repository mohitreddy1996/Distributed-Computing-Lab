from flask import Flask

from math import sin, cos

from flask.ext.spyne import Spyne

from spyne.protocol.http import HttpRpc
from spyne.protocol.soap import Soap11
from spyne.protocol.json import JsonDocument

from spyne.model.primitive import Unicode, Integer, Double
from spyne.model.complex import Iterable, ComplexModel

import logging

h = logging.StreamHandler()
rl = logging.getLogger()
rl.setLevel(logging.DEBUG)
rl.addHandler(h)

app = Flask(__name__)

spyne = Spyne(app)

class ArithmeticServiceResponse(ComplexModel):
	__namespace__ = 'tns'
	ans_ = Integer(min_occurs=0, max_occurs=1, nillable=True)
    
class TrignometricServiceResponse(ComplexModel):
	__namespace__ = 'tns'
	ans_ = Double(min_occurs=0, max_occurs=1, nillable=True)


class ArithmeticService(spyne.Service):
  __service_url_path__ = '/soap/ArithmeticService'
  __in_protocol__ = Soap11(validator='lxml')
  __out_protocol__ = Soap11()

  @spyne.srpc(Integer, Integer, _returns=ArithmeticServiceResponse)
  def add(first_, second_):
		return ArithmeticServiceResponse(ans_ = first_ + second_)
    
  @spyne.srpc(Integer, Integer, _returns=ArithmeticServiceResponse)
  def subtract(first_, second_):
		if first_ is None or second_ is None:
			return None
		return ArithmeticServiceResponse(ans_ = first_ - second_)


class TrignometricService(spyne.Service):
  __service_url_path__ = '/soap/TrignometricService'
  __target_namespace__ = 'trignometric_service'
  __in_protocol__ = Soap11(validator='lxml')
  __out_protocol__ = Soap11()

  @spyne.srpc(Double, _returns=TrignometricServiceResponse)
  def sine(angle):
		return TrignometricServiceResponse(ans_ = sin(angle * 0.0174533))

  @spyne.srpc(Double, _returns=TrignometricServiceResponse)
  def cosine(angle):
		return TrignometricServiceResponse(ans_ = cos(angle * 0.0174533))


if __name__ == '__main__':
  app.run(host='0.0.0.0')
