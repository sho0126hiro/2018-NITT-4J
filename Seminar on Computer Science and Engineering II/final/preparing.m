pkg load image
mnist = load_dataset();

%use MNIST traininig datasets
train_num = 1000; % Number of Training samples (MNIST has 60,000 Training samples)
train_images = mat2gray(mnist.train_images); % normalize images
train_labels = mnist.train_labels;
train_label_vecs = zeros(10,train_num); 
for n=1:train_num
  %create training label vectors
  train_label_vecs(train_labels(n)+1, n) = 1;
end
 
%use MNIST test datasets
test_num = 500;   % Number of Test samples (MNIST has 10,000 Test samples) 
test_images = mat2gray(mnist.test_images); % normalize images
test_labels = mnist.test_labels;
test_label_vecs = zeros(10,test_num);
for n=1:test_num
  %create test label vectors
  test_label_vecs(test_labels(n)+1, n) = 1;
end
