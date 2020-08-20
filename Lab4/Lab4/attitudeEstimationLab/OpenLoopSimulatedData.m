clear;
clear clc;
close all;

dT=1/50; % time step is in 50Hz
[Acc,Mag,wGyro,Eul]=CreateTrajectoryData(dT,1);
bias=[mean(Acc(1:50,1:3)) mean(Mag(1:50,1:3)) mean(wGyro(1:50,1:3))];

rotX=[1 0 0; 0 cosd(Eul(50,1)) sind(Eul(50,1)); 0 -sind(Eul(50,1)) cosd(Eul(50,1))];
rotY=[cosd(Eul(50,2)) 0 -sind(Eul(50,2)); 0 1 0; sind(Eul(50,2)) 0 cosd(Eul(50,2))];
rotZ=[cosd(Eul(50,3)) sind(Eul(50,3)) 0; -sind(Eul(50,3)) cosd(Eul(50,3)) 0; 0 0 1];
Ro=rotX*rotY*rotZ
R=Ro;
rows=size(Acc);

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

quiver3([0,0,0],[0,0,0],[0,0,0],[nvector(1),evector(1),dvector(1)],[nvector(2),evector(2),dvector(2)],[nvector(3),evector(3),dvector(3)],0);
pause
for i=51:rows,
    w=wGyro(i,:)-bias(7:9);
    R=IntegrateOpenLoop(R,w,dT);
    Euler=(180/pi)*[atan2(R(2,3),R(3,3)) -asin(R(1,3)) atan2(R(1,2),R(1,1))];
    newNVector=R'*nvector;
    newEVector=R'*evector;
    newDVector=R'*dvector;
    quiver3([0,0,0],[0,0,0],[0,0,0],[newNVector(1),newEVector(1),newDVector(1)],[newNVector(2),newEVector(2),newDVector(2)],[newNVector(3),newEVector(3),newDVector(3)],0);
    pause;
end
hold off