

x=0:.1:10;

tsinc= 1-x.^2/factorial(3)+x.^4/factorial(5)-x.^6/factorial(7)+x.^8/factorial(9);
asinc=sinc(x/pi);
figure;
plot(x,tsinc);
figure;
plot(x,tsinc-asinc)
figure;
plot(x,asinc)