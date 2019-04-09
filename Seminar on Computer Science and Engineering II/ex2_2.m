x = [0,0,1,1;
       0,1,0,1];
w = [  2,2;
        -2,-2];
h = [1;
       -3];
u = [2,2];
g = [3];
layer1 = FormalNeuronLayer(w,h);
layer2 = FormalNeuronLayer(u,g);

y = layer1.forward(x)
z = layer2.forward(y)