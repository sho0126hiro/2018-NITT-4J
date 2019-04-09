## Copyright (C) 2018 sho_local
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} FormalNeuronLayer (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: sho_local <sho_local@LAPTOP-LOD2Q99V>
## Created: 2018-11-05

classdef FormalNeuronLayer
  properties
    weights;
    threshold;
  end
  methods
    function obj = FormalNeuronLayer(w,h)
      obj.weights = w;
      obj.threshold = h;
    end
    function y = forward(obj, x)
      p = obj.weights * x;
      y = p > obj.threshold;
    end
  end
end
