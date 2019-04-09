x = [0,0,0,0,1,1,1,1;
     0,0,1,1,0,0,1,1;
     0,1,0,1,0,1,0,1];

w = [0.5, 1.0, 0.5;
     0.0, 0.5, 1.0;
     1.0, 0.5, 0.0];
b = [-0.5;
     -1.0;
     -0.0];

u = [1.0, 0.5, 0.0;
     0.5, 0.0, 1.0];
c = [-1.0;
     -0.0];

layer1 = Affine(w,b);
layer2 = Sigmoid();
layer3 = Affine(u,c);
layer4 = Sigmoid();

p = layer1.forward(x);
y = layer2.forward(p)
q = layer3.forward(y);
z = layer4.forward(q)
