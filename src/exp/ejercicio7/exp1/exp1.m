%==================================ARISTAS===============================================

% Procesado de los datos
[n_x_aristas_ej4, y_aristas_ej4, e_aristas_ej4, cant_aristas_ej4] = leer_datos_float('aristas-ej4-exp1-f3.txt');
[n_x_aristas_ej5, y_aristas_ej5, e_aristas_ej5, cant_aristas_ej5] = leer_datos_float('aristas-ej5-exp1-f3-tipo1.txt');
[n_x_aristas_ej6, y_aristas_ej6, e_aristas_ej6, cant_aristas_ej6] = leer_datos_float('aristas-ej6-exp1-f3-tipo1.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');

figure;

hold on;
%x = gca;
%xlim([0 dim]);
%ylim([0 80]);
stem(n_x_aristas_ej4, y_aristas_ej4, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
stem(n_x_aristas_ej5, y_aristas_ej5, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'green');
stem(n_x_aristas_ej6, y_aristas_ej6, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'blue');
xlabel('n','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
legend('Ejercicio 4','Ejercicio 5','Ejercicio 6','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1-aristas', filetype);


%==================================TIEMPO===============================================
[n_x_tiempos_ej4, y_tiempos_ej4, e_tiempos_ej4, cant_tiempos_ej4] = leer_datos_float('tiempos-ej4-exp1-f3.txt');
[n_x_tiempos_ej5, y_tiempos_ej5, e_tiempos_ej5, cant_tiempos_ej5] = leer_datos_float('tiempos-ej5-exp1-f3-tipo1.txt');
[n_x_tiempos_ej6, y_tiempos_ej6, e_tiempos_ej6, cant_tiempos_ej6] = leer_datos_float('tiempos-ej6-exp1-f3-tipo1.txt');


figure;

hold on;
%x = gca;
xlim([10 70]);
ylim([0 17]);
%h=plot(t_vec,complejidad_por_constante,'r');  %complejidad
errorbar(n_x_tiempos_ej4, y_tiempos_ej4, e_tiempos_ej4, 'r');
errorbar(n_x_tiempos_ej5, y_tiempos_ej5, e_tiempos_ej5, 'g');
errorbar(n_x_tiempos_ej6, y_tiempos_ej6, e_tiempos_ej6, 'b');
xlabel('n','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Ejercicio 4','Ejercicio 5','Ejercicio 6','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1-tiempos', filetype);
