%data generation
data_num=300;
xdata = 4*rand(2,data_num)-2;
labels = xdata(1,:).*exp(-xdata(1,:).^2 - xdata(2,:).^2) + 0.5;

%display input data
figure(1);
scatter3(xdata(1,:), xdata(2,:), labels, 10);
title('input data');

IU = 2;     % a number of input neurons
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
[X1 X2] = meshgrid(-2:0.1:2);
pt = layer1.forward([X1(:)';X2(:)']);
yt = layer2.forward(pt);
qt = layer3.forward(yt);
zt = layer4.forward(qt);
figure(3);
zsize = sqrt(size(zt));
mesh(X1,X2,reshape(zt,[zsize(2),zsize(2)]));
title('learning results')

