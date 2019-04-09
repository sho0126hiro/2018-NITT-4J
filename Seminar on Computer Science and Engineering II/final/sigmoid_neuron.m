function y = sigmoid_neuron(x,w,b)
  p = w*x + b;
  y = 1 ./ (1 + exp(-p));
end
