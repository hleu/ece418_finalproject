%% input logo and output image with message
clear; clc;
Message = fileread('output/test.txt');
output_img_file = 'output/output.png';
org_message = 'output/msg.txt';
range = 100;

%% black and white
I = imread('image/lena.png');
subplot(2,2,1); imagesc(I); title('original image'); colormap(gray); 
F = fft2(double(I));
F2 = fftshift(F);

subplot(2,2,2); imagesc(log(abs(F2)));title('original image fft');  
[M N] = size(F);
ci = round(M/2)+1; cj = round(N/2)+1;
lr = M/4; hr = M/4+range;
Mlen = length(Message);   m=1;
for (i=1:hr)
    for (j=1:hr)
        r = sqrt(i*i + j*j);
        if ((r > lr) && (r < hr))
           if (m <= Mlen)
               F2(i+ci, j+cj) = double(Message(m));
               F2(i+ci, -j+cj) = F2(i+ci, j+cj);
               F2(-i+ci, j+cj) = F2(i+ci, j+cj);
               F2(-i+ci, -j+cj) = F2(i+ci, j+cj);
               m = m+1;
           end;
        end;
    end;
end;
if (m < Mlen)
    disp('Error!!! Message too long');
    disp(['Message length: ',num2str(Mlen),'; For input image, can only display message with length up to: ',num2str(m)])
end

subplot(2,2,3);  imagesc(log(abs(F2))); title('fft image with message'); 
F = ifftshift (F2);
J = ifft2(F); norm(imag(J));
subplot(2, 2, 4); imagesc(J);  title('image with hidden message'); suptitle('Hidden-message-adding steps');
figure; imagesc(J); colormap(gray);
imwrite(uint8(J), output_img_file);

%% get the different image
clc;
J2 = imread(output_img_file);
J2 = double(J2);
for (i=1:M)
    for (j=1:N)
        diff(i,j) = J(i,j) - J2(i,j);
    end
end

%%
% Retrieve
J = imread(output_img_file);
J = double(J);

[M N] = size(J);
for (i=1:M)
    for (j=1:N)
        J(i,j) =  J(i,j) + diff(i,j);
    end
end
%%
F = fft2(J);
F2 = fftshift(F);
Mlen = length(Message); m = 1;
fileID = fopen(org_message,'w');
for (i=1:hr)
    for (j=1:hr)
        r = sqrt(i*i + j*j);
        if ((r > lr) && (r < hr))
           if (m <= Mlen)
               fprintf(fileID, '%c', char(uint8(real(F2(i+ci, j+cj)))));
               m = m +1;
           end
        end;
    end;
end;

%% calculate MSE
org = double(I);
MSE = 0;
for (i=1:M)
    for (j=1:N)
        MSE =  MSE + (org(i,j) - J(i,j))*(org(i,j) - J(i,j));
    end
end
MSE = MSE/(M*N)
%% rgb image
rgb_img = imread('test.png');
I = .2989*rgb_img(:,:,1)...
    +.5870*rgb_img(:,:,2)...
    +.1140*rgb_img(:,:,3);
