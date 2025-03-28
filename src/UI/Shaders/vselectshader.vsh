precision highp float;
attribute highp vec4 a_position;

uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;

//установить вершину в нужную позицию в соответствии со всеми преобразованиями
void main(void)
{
    //перемножение матриц даёт матрицу преобразований, которая устанавливает вершину туда, куда нам надо
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}
