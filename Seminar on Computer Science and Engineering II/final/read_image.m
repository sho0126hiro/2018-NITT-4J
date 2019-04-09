function sample_dataset=read_image()

  imgDirName = 'sampledata';
  csvfile = 'list.csv';

  if exist(imgDirName)
    if exist(strcat(imgDirName, '/', csvfile))
    else
      fprintf(strcat('csv file "', csvfile, '" Not found\n'));
      return;
    end
  else
    fprintf(strcat('imgDirName "', imgDirName,'" Not Found\n'));
    return;
  end
 
  csvdata = importdata(strcat(imgDirName, '/', csvfile), ',');
  ss= size(csvdata.data);
  imgNum = ss(1);
  if imgNum == 0
    fprintf('There are no image files. Please put .png files under ./sampledata');
  else
    for i=1:imgNum
      imgFileName = char(csvdata.textdata(i));
      img = imread(strcat(imgDirName, '/', imgFileName));
      if ndims(img) == 3
          img = img(:,:,1);
      end
      img = imresize(img, [28,28]);
      out_images(:,:,1,i) = uint8(-1 .* (int16(im2uint8(img)) - 255));
      out_labels(i,1) = csvdata.data(i);
    end
  end
  
  sn = randperm(imgNum);
  sample_dataset.test_images = out_images(:,:,1,sn(1:1288));
  sample_dataset.test_labels = out_labels(sn(1:1288),1);
  sample_dataset.train_images = out_images(:,:,1,sn(1:1000));
  sample_dataset.train_labels = out_labels(sn(1:1000),1);
  %sample_dataset.test_images = out_images(:,:,1,sn(1001:end));
  %sample_dataset.test_labels = out_labels(sn(1001:end),1);
end

  

