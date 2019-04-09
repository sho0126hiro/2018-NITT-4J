function loss = loss_function(z,t)
      [row, col] = size(z);
      loss = sum(sum((z-t).^2)) / (2*col);
end