% Calculate train accuracy
train_res_mat = zeros(10, 10);
for n=1:train_num
  img = train_images(:,:,1,n);
  x = img(:);
  y = sigmoid_neuron(x,w,b);
  z = sigmoid_neuron(y,u,c);
  [value, index] = max(z);
  train_res_mat(index, train_labels(n)+1) = ...
    train_res_mat(index, train_labels(n)+1) + 1;
end
train_res_mat
train_accuracy = trace(train_res_mat)/sum(sum(train_res_mat))
