classdef MSE < handle
  properties
    z;
    t;
  end
  methods      
    function loss = forward(obj, z, t)
      obj.z = z;
      obj.t = t;
      [row, col] = size(z);
      loss = sum(sum((z-t).^2)) / (2*col);
    end
    
    function dL = backward(obj)
      dL = obj.z - obj.t;
    end
  end
end
