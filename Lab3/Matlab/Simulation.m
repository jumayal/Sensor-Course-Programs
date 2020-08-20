%Create Tumble data within A and M
[A M Ad Bd]=CreateTumbleData(1000)

sF_Accelerometer= 9.8./max(A)
sF_magnetometer =47835 ./ max(M)

nAx=sF_Accelerometer(1)*(A(:,1)- mean(A(:,1)))
nAy=sF_Accelerometer(2)*(A(:,2)-mean(A(:,2)))
nAz=sF_Accelerometer(3)*(A(:,3)-mean(A(:,3)))

calibratedA=[nAx nAy nAz]
norm_CalibratedA= sqrt((calibratedA(:,1).^2)+(calibratedA(:,2).^2)+(calibratedA(:,3).^2))
norm_A= sqrt((A(:,1)*sF_Accelerometer(1)).^2+(A(:,2)*sF_Accelerometer(2)).^2+(A(:,3)*sF_Accelerometer(3)).^2)

calibratedM=[sF_magnetometer(1)*(M(:,1)- mean(M(:,1))) sF_magnetometer(2)*(M(:,2)- mean(M(:,2))) sF_magnetometer(3)*(M(:,3)- mean(M(:,3)))]
norm_CalibratedM= sqrt((calibratedM(:,1).^2)+(calibratedM(:,2).^2)+(calibratedM(:,3).^2))
norm_M= sqrt((M(:,1)*sF_magnetometer(1)).^2+(M(:,2)*sF_magnetometer(2)).^2+(M(:,3)*sF_magnetometer(3)).^2)

%Plotting Norm to see the different and linearization
figure;
scatter(1:1000,norm_CalibratedA,'filled');
hold on;
scatter(1:1000,norm_A,'filled');
legend('Calibrated','Original')
hold off

%Histagram for Accelerometer
figure;
subplot(2,1,2)
histfit(norm_CalibratedA)
title('Calibrated Accelerometer Data')
xlabel('Acceleration (m/s)') 
ylabel('Bin') 

subplot(2,1,1)
histfit(norm_A)
title('Original Accelerometer Data')
xlabel('Acceleration (m/s)') 
ylabel('Bin') 

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