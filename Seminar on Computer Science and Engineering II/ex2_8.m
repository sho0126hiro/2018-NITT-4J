clear all
 
xdata = [0,0,1,1;
         0,1,0,1];
labels = [0,1,1,0];
data_num=4;
 
IU = 2;     % a number of input neurons
HU = 2;     % a number of hidden neurons
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

p = layer1.forward(xdata);
y = layer2.forward(p)
q = layer3.forward(y);
z = layer4.forward(q)
loss = layer5.forward(z,labels)
