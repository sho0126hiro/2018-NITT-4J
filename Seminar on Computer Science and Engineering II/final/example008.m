
IU = 784; % a number of input neurons (28*28)
HU = 30;  % a number of hidden neurons
OU = 10;  % a number of output neurons
 
w = 2.0*rand(HU,IU) - 1.0;
b = 2.0*rand(HU,1) - 1.0;
u = 2.0*rand(OU,HU) - 1.0;
c = 2.0*rand(OU,1) - 1.0;
 
EPOCH=50;  % a number of training epochs
LAMBDA=0.1; % learning rate

for epoch=1:EPOCH
  for n=1:train_num
    img = train_images(:,:,1,n);
    x = img(:);
    y = sigmoid_neuron(x,w,b);
    z = sigmoid_neuron(y,u,c);
    t = train_label_vecs(1:10,n);
    o(1:10,n)=z;
    
    delta_out = (z-t).*(z.*(1-z)); %sigmoid backward
    delta_hidden = (delta_out'*u)'.*(y.*(1-y)); %affine backward
    
    %update
    u=u-LAMBDA * delta_out * y';
    c=c-LAMBDA * delta_out;
    w=w-LAMBDA * delta_hidden * x';
    b=b-LAMBDA * delta_hidden;
  end
 
  % calculate current LOSS
  loss(epoch) = loss_function(o, train_label_vecs);
end
 
%%%%%%%%%% Display the results %%%%%%%%%%%%%%%
% Display cost change graph
figure(1);
plot([1:epoch], loss)
title('Cost on the training data');
xlabel('Epoch');
ylabel('Cost');
 
% Calculate train accuracy
train_res_mat = zeros(10, 10);
for n=1:train_num
  img = train_images(:,:,1,n);
  x = img(:);
  y = sigmoid_neuron(x,w,b);
  z = sigmoid_neuron(y,u,c);
  [value, index] = max(z);
  train_res_mat(index, train_labels(n)+1) = train_res_mat(index, train_labels(n)+1) + 1;
end
train_res_mat
train_accuracy = trace(train_res_mat)/sum(sum(train_res_mat))
 
% Calculate test accuracy
test_res_mat = zeros(10, 10);
for n=1:test_num
  img = test_images(:,:,1,n);
  x = img(:);
  y = sigmoid_neuron(x,w,b);
  z = sigmoid_neuron(y,u,c);
  [value, index] = max(z);
  test_res_mat(index, test_labels(n)+1) = test_res_mat(index, test_labels(n)+1) + 1;
end
test_res_mat
test_accuracy = trace(test_res_mat)/sum(sum(test_res_mat))



