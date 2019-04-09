function mnist = load_dataset(varargin)
%LOADMNISTDATASET Load MNIST Dataset.
%
%  mnist = loadMNISTDataset(...)
%
% Options
%
%     'TrainLabelsFile'  default: 'data/mnist/train-labels-idx1-ubyte'
%     'TrainImagesFile'  default: 'data/mnist/train-images-idx3-ubyte'
%     'TestLabelsFile'   default: 'data/mnist/t10k-labels-idx1-ubyte'
%     'TestImagesFile'   default: 'data/mnist/t10k-images-idx3-ubyte'
%
% Output
%
%   mnist: struct with the following fields
%     train_labels: 60000-by-1 uint8 array.
%     train_images: 28-by-28-by-1-by-60000 uint8 array.
%     test_labels: 10000-by-1 uint8 array.
%     test_images: 28-by-28-by-1-by-10000 uint8 array.
%
  options.train_labels_file = 'data/mnist/train-labels-idx1-ubyte';
  options.train_images_file = 'data/mnist/train-images-idx3-ubyte';
  options.test_labels_file = 'data/mnist/t10k-labels-idx1-ubyte';
  options.test_images_file = 'data/mnist/t10k-images-idx3-ubyte';
  options = getOptions(options, varargin{:});

  mnist.train_labels = loadMNISTLabels(options.train_labels_file);
  mnist.train_images = loadMNISTImages(options.train_images_file);
  mnist.test_labels = loadMNISTLabels(options.test_labels_file);
  mnist.test_images = loadMNISTImages(options.test_images_file);
end

function labels = loadMNISTLabels(filename)
%LOADMNISTLABELS Return a [number of MNIST images]x1 matrix containing
%the labels for the MNIST images.
%
% http://ufldl.stanford.edu/wiki/index.php/Using_the_MNIST_Dataset
  fprintf('Loading %s\n', filename);
  fp = fopen(filename, 'rb');
  assert(fp ~= -1, ['Could not open ', filename, '']);
  magic = fread(fp, 1, 'int32', 0, 'ieee-be');
  assert(magic == 2049, ['Bad magic number in ', filename, '']);
  numLabels = fread(fp, 1, 'int32', 0, 'ieee-be');
  labels = fread(fp, inf, 'uint8=>uint8');
  assert(size(labels,1) == numLabels, 'Mismatch in label count');
  fclose(fp);
end

function images = loadMNISTImages(filename)
%LOADMNISTIMAGES Return a 28x28x1x[number of MNIST images] uint8 array
%containing the raw MNIST images.
%
% http://ufldl.stanford.edu/wiki/index.php/Using_the_MNIST_Dataset
  fprintf('Loading %s\n', filename);
  fp = fopen(filename, 'rb');
  assert(fp ~= -1, ['Could not open ', filename, '']);
  magic = fread(fp, 1, 'int32', 0, 'ieee-be');
  assert(magic == 2051, ['Bad magic number in ', filename, '']);
  numImages = fread(fp, 1, 'int32', 0, 'ieee-be');
  numRows = fread(fp, 1, 'int32', 0, 'ieee-be');
  numCols = fread(fp, 1, 'int32', 0, 'ieee-be');
  images = fread(fp, inf, 'uint8=>uint8');
  fclose(fp);
  images = reshape(images, numCols, numRows, 1, numImages);
  images = permute(images,[2, 1, 3, 4]);
end
