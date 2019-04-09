clear all
 
xdata = [0,0,1,1;
         0,1,0,1];
labels = [0,0,0,1];
data_num=4;
 
w = 2.0*rand(1,2) - 1.0;
b = 2.0*rand(1,1) - 1.0;

layer1 = Affine(w,b);
layer2 = Sigmoid();
layer3 = MSE();

% a number of training
EPOCH=1000;
% learning rate
LAMBDA=0.1; 
for epoch=1:EPOCH
  p = layer1.forward(xdata);
  y = layer2.forward(p);
  loss(epoch) = layer3.forward(y,labels);
  
  %calculate gradient
  dy = layer3.backward();
  dp = layer2.backward(dy);
  dx = layer1.backward(dp);
  
  %learning weights and biases
  layer1.update(LAMBDA);
end

loss

% Display loss change graph
figure(1);
plot(loss)
xlabel('Epoch');
ylabel('LOSS');
