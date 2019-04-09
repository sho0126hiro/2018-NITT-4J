x = [0,0,0,0,1,1,1,1;
     0,0,1,1,0,0,1,1;
     0,1,0,1,0,1,0,1];

w = [0.5, 1.0, 0.5;
     0.0, 0.5, 1.0;
     1.0, 0.5, 0.0];
h = [0.5;
     1.0;
     0.0];

u = [1.0, 0.5, 0.0;
     0.5, 0.0, 1.0];
g = [1.0;
     0.0];
     
layer1 = FormalNeuronLayer(w,h);
layer2 = FormalNeuronLayer(u,g);
     
y = layer1.forward(x)
z = layer2.forward(y)
