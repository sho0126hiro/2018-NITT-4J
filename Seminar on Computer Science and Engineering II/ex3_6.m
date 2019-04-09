data_num=50;
xdata = 15*rand(1,data_num);
labels = (sin(xdata)+1)/2; % between 0 and 1
 
figure(1)
scatter(xdata, labels);
xlim([0,15])

IU = 1;     % a number of input neurons
HU = 30;     % a number of hidden neurons
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

EPOCH=20000; % a number of training epochs
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

% Display loss change graph
figure(2);
plot(loss)
axis([0 EPOCH 0 max(loss)])
xlabel('Epoch');
ylabel('LOSS');

% Display output graph
xt = [0:0.01:15];
pt = layer1.forward(xt);
yt = layer2.forward(pt);
qt = layer3.forward(yt);
zt = layer4.forward(qt);

figure(3);
plot(xt,zt)
xlim([0,15])
