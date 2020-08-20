close all;

[A M Ad Bd]=CreateTumbleData(1000);

%scale_Factor_Accelerometer=4/65535;
scale_Factor_Accelerometer=1/ (0.5*((2^15)-1));
scaled_A= A.*scale_Factor_Accelerometer;

scale_Factor_Magnetometer=0.15;
scaled_M=M.*scale_Factor_Magnetometer;

[Atile,Btile]=CalibrateEllipsoidData3D(scaled_A(:,1),scaled_A(:,2),scaled_A(:,3),19,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scaled_A(:,1),scaled_A(:,2),scaled_A(:,3),Atile,Btile);

norm_CalibratedA= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))
norm_A= sqrt(scaled_A(:,1).^2+scaled_A(:,2).^2+scaled_A(:,3).^2)

figure;
subplot(2,1,2)
histfit(norm_CalibratedA)
title('Calibrated Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin') 

subplot(2,1,1)
histfit(norm_A)
title('Original Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin') 

[Atile,Btile]=CalibrateEllipsoidData3D(scaled_M(:,1),scaled_M(:,2),scaled_M(:,3),19,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scaled_M(:,1),scaled_M(:,2),scaled_M(:,3),Atile,Btile);

norm_CalibratedB= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))
norm_B= sqrt(scaled_M(:,1).^2+scaled_M(:,2).^2+scaled_M(:,3).^2)

%Histagram for Magnetometer
figure;
subplot(2,1,2)
histfit(norm_CalibratedM)
title('Calibrated Magnetometer Data')
xlabel('Magnetic Field (nT)') 
ylabel('Bin') 

subplot(2,1,1)
histfit(norm_M)
title('Original Magnetometer Data')
xlabel('Magnetic Field 9(nT)') 
ylabel('Bin') 


standard_Deviation_Accelerometer=std(norm_CalibratedA);
average_Accelerometer=mean(norm_CalibratedA)
standard_Deviation_Magnetometer=std(norm_CalibratedM);
average_Magnetometer=mean(norm_CalibratedM)
T=table(standard_Deviation_Magnetometer,average_Magnetometer,standard_Deviation_Accelerometer,average_Accelerometer)