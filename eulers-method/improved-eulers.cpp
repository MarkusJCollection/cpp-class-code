#include <iostream>

// Our function used for evaluating the new predicted y value given an x, y, derivative function, and step size.
double find_new_y(double x_val, double y_val, double (*derivative)(double, double), double step) {
	return y_val + derivative(x_val, y_val) * step;
}

// Our function used for evaluating the new predicted y value using the backwards euler method
//given an x, y, deriviative function, step size, and number of iterations.
void backwards_euler_method(double &x_val, double &y_val, double(*derivative)(double, double), 
							 double step, int num_iterations) {

	double precision = 0.00001;
	int max_depth = 750;
	int dpth = 0;
	double new_x = -1;
	double a;
	double b;

	auto func = [&](double y) -> double {return y - y_val - step * derivative(x_val, y);};

	for (int i = 0; i < num_iterations; i++) {

		a = y_val;
		b = 2*a;
		x_val += step;

		while ((abs(b - a) > precision) && dpth < max_depth) {
			double a_eval = func(a);
			double b_eval = func(b);
			new_x = b - (b_eval / ((b_eval - a_eval) / (b - a)));
			a = b;
			b = new_x;
			dpth++;
		}

		if (dpth > max_depth) {
			std::cout << "\n\n-==-Reached max while depth.-==-\n\n";
		}

		dpth = 0;
		y_val = new_x;
	}
}

// Our function for enacting eulers method given an x, y, step size, and number of iterations.
void eulers_method(double &x_val, double &y_val, double (*derivative)(double, double), 
				   double step, int num_iterations) {

	for (int i = 0; i < num_iterations; i++) {
		y_val = find_new_y(x_val, y_val, derivative, step);
		x_val += step;
	}
}

// Our function using improved eulers method given an x, y, derivative function, step size, and number of iterations.
void improved_eulers_method(double &x_val, double &y_val, 
							double (*derivative)(double, double), 
							double step, int num_iterations) {

	double tmp_x;
	double tmp_y;

	for (int i = 0; i < num_iterations; i++) {
		tmp_x = x_val;
		tmp_y = y_val;
		
		y_val = find_new_y(x_val, y_val, derivative, step);
		x_val += step;
		y_val = tmp_y + (step / 2 * (derivative(tmp_x, tmp_y) + derivative(x_val, y_val)));

	}
}

// Our function used to calculate the derivative given an x and y value.
double deriv_func(double x_val, double y_val) {
	return 3 + x_val - y_val;
}

double deriv_two(double x_val, double y_val) {
	return (2 * x_val) - (3 * y_val) + 1;
}

double deriv_three(double x_val, double y_val) {
	return (4 * x_val) - (2 * y_val);
}

double deriv_four(double x_val, double y_val) {
	return (x_val * pow(y_val, 2) - (y_val / x_val));
}

int main() {

	/*
	Editing the con
	*/

	const double init_x = 1;
	const double init_y = 1;
	const double step = 0.1;
	const int num_it = 5;

	double x_val = init_x;
	double y_val = init_y;




	std::cout << "Number of iterations: " << num_it << "\nStep size: " << step << "\n\n";

	eulers_method(x_val, y_val, deriv_four, step, num_it);
	
	std::cout << "Eulers Method:\n";
	std::cout << "New X Value: " << x_val << "\nPredicted Y Value: " << y_val << "\n\n";

	x_val = init_x;
	y_val = init_y;
	
	improved_eulers_method(x_val, y_val, deriv_four, step, num_it);

	std::cout << "Improved Eulers Method:\n";
	std::cout << "New X Value : " << x_val << "\nPredicted Y Value : " << y_val << "\n\n";

	x_val = init_x;
	y_val = init_y;

	backwards_euler_method(x_val, y_val, deriv_four, step, num_it);
	std::cout << "Backwards Eulers Method:\n";
	std::cout << "New X Value : " << x_val << "\nPredicted Y Value : " << y_val << "\n";


	return 0;
}