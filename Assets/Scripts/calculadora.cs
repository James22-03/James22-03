using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class calculadora : MonoBehaviour {

    public Text resultado;
    public Text resultado2;
    public Text resultado3;
    public Text resultado4;
    string operacion;
    private string textoimprimir;
    string valor1;
    string valor2;
    string operacionActual;
    public void BorrarC()
    {
        resultado.text = "";
	resultado2.text= "";
	resultado3.text= "";
	resultado4.text= "";
    }

    public void area()
    {
        if(resultado.text != "")
        {
            operacion = "1";
	    valor2 = resultado.text;
            valor1 = resultado2.text;
            operacionActual = operacion;
            resultado3.text = operaciones(valor1, valor2, operacionActual);
        }
        
    }

    public void presupuesto()
    {
        if(resultado.text != "")
        {
            operacion = "2";
	    valor2 = resultado.text;
            valor1 = resultado2.text;
            operacionActual = operacion;
            resultado4.text = operaciones(valor1, valor2, operacionActual);
        }
        
    }
    public string operaciones(string n1, string n2, string opeMath)
    {
        string respuesta = "";
        switch (opeMath)
        {
            case "1":
                respuesta = (double.Parse(n1) * double.Parse(n2)).ToString();
                break;
            case "2":
                double num1 = double.Parse(n1);
	double num2 = double.Parse(n2);
	double superficie = num1 * num2;
	double cantidad1 = superficie * 5;
	double cantidad2 = superficie * 3;
	double precio1 = cantidad1 * 15;
	double precio2 = cantidad2 * 15;
	double sueldo = superficie * 60;
	double preciofinal1 = precio1+sueldo;
	double preciofinal2 = precio2+sueldo;
	respuesta = "-->La superficie es de: "+superficie.ToString()+" m2"+
	"\n-->Cantidad de estuco a utilizar: \n\t-->En una capa es de: "+cantidad2.ToString()+" kg \n\t-->En dos capas es de: "+cantidad1.ToString()+" kg"+
	"\n-->Gasto en material: \n\t-->En una capa: $"+precio2.ToString()+".00\n\t-->En dos capas: $"+ precio1.ToString()+".00"+
	"\n-->La mano de obra se estima en: $"+sueldo.ToString()+".00"+
	"\n-->Generando un costo total de: \n\t-->$"+preciofinal2.ToString()+".00 en una capa\n\t-->$"+preciofinal1.ToString()+".00 en dos capas";
                break;
            case "*":
                respuesta = (double.Parse(n1) * double.Parse(n2)).ToString();
                break;
            case "/":
                if (!n2.Equals("0"))
                {
                    respuesta = (double.Parse(n1) / double.Parse(n2)).ToString();
                } else
                {
                    respuesta = "La divicion por 0 no es posible";
                } 
                break;
        }
        return respuesta;
    }
}
