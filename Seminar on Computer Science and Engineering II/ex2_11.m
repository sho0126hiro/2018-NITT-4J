clear all

xdata = [0,0,0,0,1,1,1,1;
             0,0,1,1,0,0,1,1;
             0,1,0,1,0,1,0,1];
             
labels = [0,1,1,0,1,0,0,1];
data_num=8;
 
IU = 3;     % a number of input neurons
HU = 3;     % a number of hidden neurons
OU = 1;     % a number of output neurons
 
% initialize weights and biases
% as random numbers between -1.0 and 1.0.
w = 2.0*rand(HU,IU) - 1.0;
b = 2.0*rand(HU,1) - 1.0;
u = 2.0*rand(OU,HU) - 1.0;
c = 2.0*rand(OU,1) - 1.0;

layer1 = Affine(w,b);
layer2 = Sigmoid();
layer3 = Affine(u,c);
layer4 = Sigmoid();
layer5 = MSE();

EPOCH=1000; % a number of training epochs
LAMBDA=0.1; % learning rate

for epoch=1:EPOCH
  p = layer1.forward(xdata);
  y = layer2.forward(p);
  q = layer3.forward(y);
  z = layer4.forward(q);
  loss(epoch) = layer5.forward(z,labels);
  
  %calculate gradient
  dz = layer5.backward();
  dq = layer4.backward(dz);
  dy = layer3.backward(dq);
  dp = layer2.backward(dy);
  dx = layer1.backward(dp);
  
  %learning weights and biases
  layer1.update(LAMBDA);
  layer3.update(LAMBDA);
end

loss

% Display loss change graph
figure(1);
plot(loss)
xlabel('Epoch');
ylabel('LOSS');
