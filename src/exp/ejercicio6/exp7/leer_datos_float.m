function [x, y, e, c] = leer_datos_float(file)
    data = fopen(file)
    c = fscanf(data, '%lu', 1);
    cant = c + 1;
    A = fscanf(data, '%f', [cant Inf]);
    A = A'; %aca esta bien la matriz
    [Y, I] = sort(A(1,:)); % ordenamos A de acuerdo a su primer columna
    x = A(:,1);%aca pone la primera columna de la matriz en x

    d = A;
    d(:,1) = [];
    A = A(:,I); %aca pasa la primera columna de la matriz a la ultima <--- Esta linea es la que cambie de lugar
    y = mean(d, 2);
    e = std(d, 1, 2);

    fclose(data);
end
