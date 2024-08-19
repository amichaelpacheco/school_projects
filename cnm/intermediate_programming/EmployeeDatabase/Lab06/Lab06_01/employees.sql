DROP TABLE salariedEmployees;
DROP TABLE commissionEmployees;
DROP TABLE employees;

CREATE TABLE employees(
	ssn varchar (30) NOT NULL,
	first_name varchar (30) NOT NULL,
	last_name varchar (30) NOT NULL,
	birthday date NOT NULL,
	employeeType varchar (30) NOT NULL,
	departmentName varchar (30) NOT NULL,
	PRIMARY KEY (ssn)
);
CREATE TABLE salariedEmployees(
	ssn varchar (30) NOT NULL,
	weeklySalary real NOT NULL,
	bonus real,
	PRIMARY KEY (ssn),
	FOREIGN KEY (ssn)  REFERENCES employees(ssn)
);
CREATE TABLE commissionEmployees(
	ssn varchar (30) NOT NULL,
	gross_sales int NOT NULL,
	commission_rate real NOT NULL,
	bonus real,
	PRIMARY KEY (ssn),
	FOREIGN KEY (ssn) REFERENCES employees(ssn)
);