clear;
clear clc;
close all;

filename = 'better_tens.csv';
real_data=csvread(filename);
wGyro=real_data;
dT=1/50; % time step is in 50Hz

bias=[67.557 57.504 -287.154];

R=eye(3);
rows=size(wGyro);

nvector=[1;0;0];
evector=[0;-1;0];
dvector=[0;0;-1];
[sX,sY,sZ]=sphere(30);
surf(sX,sY,sZ,'FaceAlpha',.1,'EdgeColor','none');
axis equal;
xlabel('x')
ylabel('y')
zlabel('z')
hold on

%quiver3([0,0,0],[0,0,0],[0,0,0],[nvector(1),evector(1),dvector(1)],[nvector(2),evector(2),dvector(2)],[nvector(3),evector(3),dvector(3)],0);
pause
for i=1:rows[1],
    w=(pi/180)*(wGyro(i,3)-bias);
    R=IntegrateOpenLoop(R,w,dT);
    %Euler=(180/pi)*[atan2(R(2,3),R(3,3)) -asin(R(1,3)) atan2(R(1,2),R(1,1))];
    Euler=[atan2(R(2,3),R(3,3)) -asin(R(1,3)) atan2(R(1,2),R(1,1))];

    disp(Euler);
    %newNVector=R'*nvector;
    %newEVector=R'*evector;
    %newDVector=R'*dvector;
    %quiver3([0,0,0],[0,0,0],[0,0,0],[newNVector(1),newEVector(1),newDVector(1)],[newNVector(2),newEVector(2),newDVector(2)],[newNVector(3),newEVector(3),newDVector(3)],0);
    pause;
end
hold off