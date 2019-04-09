x = [1,1,1;
       0,1,0;
       1,0,0;
       0,0,1];
w = [3,2,2,0;
       4,1,5,2;
       1,0,1,4;
       0,1,0,1];
h = [2;6;1;0];
u=[4,1,4,3;
     2,3,0,1;
     0,1,2,4;
     3,1,1,2];
g = [1;4;3;5];
layer1 = FormalNeuronLayer(w,h);
layer2 = FormalNeuronLayer(u,g);
y = layer1.forward(x)
z = layer2.forward(y)