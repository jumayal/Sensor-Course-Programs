filename = 'tens.csv';
M=csvread(filename);
bias=mean(M(:,1:3));