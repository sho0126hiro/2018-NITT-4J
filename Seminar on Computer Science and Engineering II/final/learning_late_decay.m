function next = learning_late_decay(init,epoch,decay)
  next = init * (1/(1+decay*epoch));
end