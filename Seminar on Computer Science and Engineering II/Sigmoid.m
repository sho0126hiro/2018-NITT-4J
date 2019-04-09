classdef Sigmoid < handle
  properties
    y;
  end
  
  methods      
    function y = forward(obj, x)
      y = 1 ./ (1 + exp(-x));
      obj.y = y;
    end
    
    function dL = backward(obj, dL0)
      dL = dL0 .* obj.y .* (1.0 - obj.y);      
    end
  end
end
