x = [0,0,1,1;
       0,1,0,1];
w = [  2,2;
        -2,-2];
b = [-1;
        3];
u = [2,2];
c = [-3];
     
layer1 = Affine(w,b);
layer2 = Sigmoid();
layer3 = Affine(u,c);
layer4 = Sigmoid();

p = layer1.forward(x);
y = layer2.forward(p)
q = layer3.forward(y);
z = layer4.forward(q)
