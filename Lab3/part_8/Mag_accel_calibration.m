close all;
xfileID= fopen('accelx.txt','r');
yfileID= fopen('accely.txt','r');
zfileID= fopen('accelz.txt','r');
formatSpec='%f';
accel_x= fscanf(xfileID,formatSpec);
accel_y= fscanf(yfileID,formatSpec);
accel_z= fscanf(zfileID,formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scale_Factor_Accelerometer_x=accel_x/ (0.5*((2^15)-1));
scale_Factor_Accelerometer_y=accel_y/ (0.5*((2^15)-1));
scale_Factor_Accelerometer_z=accel_z/ (0.5*((2^15)-1));
norm_A= sqrt(scale_Factor_Accelerometer_x.^2+scale_Factor_Accelerometer_y.^2+scale_Factor_Accelerometer_z.^2);

sf_z=accel_z.*0.00006 - 0.0086;
sf_y=accel_y.*0.00006 - 0.016;
sf_x=accel_x.*0.00006 -0.0299;

norm=sqrt(sf_z.^2+sf_x.^2+sf_y.^2);
figure;
subplot(2,1,1)
plot(norm_A);
title('Original Accelerometer Data')
ylabel('Gravity (G)')

subplot(2,1,2)
plot(norm);
title('Naive Accelerometer Data')
ylabel('Gravity (G)')

%Calibrating Accelerometer Using Matlab Function
time = 0:0.02:((length(accel_x)-1)*0.02);

[Atile,Btile]=CalibrateEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,20,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,Atile,Btile);

norm_CalibratedA= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))

figure;
subplot(2,1,1)
plot(time,norm_A);
title('Original Accelerometer Data')
xlabel('time (ms)') 
ylabel('Gravity (G)')

subplot(2,1,2)
plot(time,norm_CalibratedA);
title('Calibrated Accelerometer Data')
xlabel('time (ms)') 
ylabel('Gravity (G)') 

figure;
subplot(2,1,1)
histfit(norm_A)
title('Original Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin')

subplot(2,1,2)
histfit(norm_CalibratedA)
title('Calibrated Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin') 
%-------------------------------------------------------------------------------------------
%Calibrations for Magnetometer
%--------------------------------------------------------------------------------------------
xfileID= fopen('magx.txt','r');
yfileID= fopen('magy.txt','r');
zfileID= fopen('magz.txt','r');
formatSpec='%f';

mag_x= fscanf(xfileID,formatSpec);
mag_y= fscanf(yfileID,formatSpec);
mag_z= fscanf(zfileID,formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scaled_mag_x=mag_x*0.6;
scaled_mag_y=mag_y*0.6;
scaled_mag_z=mag_z*0.6;
norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2)

sf_z=mag_x.*0.0125 - 0.251;
sf_y=mag_y.*0.0072 - 0.122;
sf_x=mag_z.*0.0083 -0.2179;

norm=sqrt(sf_z.^2+sf_x.^2+sf_y.^2);
figure;
subplot(2,1,1)
plot(norm_M);
title('Original Magnetometer Data')
ylabel('Earth Magnetic Field')

subplot(2,1,2)
plot(norm);
title('Naive Magnetometer Data')
ylabel('Earth Magnetic Field')

%Calibrating Magnetometer using Matlab Function
[Atile,Btile]=CalibrateEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,20,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,Atile,Btile);
time = 0:0.02:((length(scaled_mag_x)-1)*0.02);

norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2)
norm_CalibratedM= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))

%Histagram for Magnetometer
figure;
subplot(2,1,1)
plot(time,norm_M);
title('Original Magnetometer Data')
ylabel('Magnetic Field (uT)') 
xlabel('time (ms)') 

subplot(2,1,2)
plot(time,norm_CalibratedM);
title('Calibrated Magnetometer Data')
ylabel('Magnetic Field (uT)') 
xlabel('time(ms)')

figure;
subplot(2,1,1)
histfit(norm_M)
title('Original Magnetometer Data')
xlabel('Magnetic Field (nT)') 
ylabel('Bin') 

subplot(2,1,2)
histfit(norm_CalibratedM)
title('Calibrated Magnetometer Data')
xlabel('Magnetic Field (nT)') 
ylabel('Bin') 

