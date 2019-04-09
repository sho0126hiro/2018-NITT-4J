classdef Affine < handle
  properties
    weights;
    bias;
    x;
    dw;
    db;
  end
	
  methods
    function obj = Affine(w,b)
      obj.weights = w;
      obj.bias = b;
    end
      
    function y = forward(obj, x)
      obj.x = x;
      p = obj.weights * x;
      y = p + obj.bias;
    end
    
    function dL = backward(obj, dL0)
      dL = obj.weights' * dL0;
      obj.dw = dL0 * obj.x';
      obj.db = sum(dL0, 2);
    end
    
    function update(obj, learning_rate)
      obj.weights = obj.weights - learning_rate * obj.dw;
      obj.bias = obj.bias - learning_rate * obj.db;
    end 
  end
end
