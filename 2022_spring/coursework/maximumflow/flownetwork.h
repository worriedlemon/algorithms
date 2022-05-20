#include "linear.h"
#include <fstream>
#include <iomanip>

#ifndef FLOWNETWORK
#define FLOWNETWORK
#define INF ((double)(1e300 * 1e300))

// Flow Network representation based on adjecency matrix
class FlowNetwork
{
	// Vertexes count
	size_t size;

	// Vertexes ID/Names
	string* vertexesNames;

	// Edges' capacities
	double** capacities;

	// Auxilliary function for drawing line in ASCII dash symbols ('-')
	void OutputLine(ostream& stream, FlowNetwork& matrix, size_t maxwidth)
	{
		stream << "--";
		for (size_t i = 0; i < maxwidth; i++) stream << '-';
		stream << "---";
		for (size_t i = 0; i < matrix.size; i++)
		{
			const size_t len = maxwidth;
			for (size_t j = 0; j < len; j++)
			{
				stream << '-';
			}
			stream << "--" << (i == matrix.size - 1 ? '\n' : '-');
		}
	}

	void SwapSourceAndDrain()
	{
		if (vertexesNames[0] != "S")
		{
			size_t index = 1;
			for (index; index < size || vertexesNames[index] != "S"; index++);
			if (index == size) throw out_of_range("Unexpected error");
			vertexesNames[index] = vertexesNames[0];
			vertexesNames[0] = "S";
			for (size_t i = 0; i < size; i++)
			{
				double temp = capacities[0][i];
				capacities[0][i] = capacities[index][i];
				capacities[index][i] = temp;
			}
			for (size_t i = 0; i < size; i++)
			{
				double temp = capacities[i][0];
				capacities[i][0] = capacities[i][index];
				capacities[i][index] = temp;
			}
		}

		if (vertexesNames[size - 1] != "T")
		{
			size_t index = 0;
			for (index; index < size - 1 || vertexesNames[index] != "S"; index++);
			if (index == size - 1) throw out_of_range("Unexpected error");
			vertexesNames[index] = vertexesNames[size - 1];
			vertexesNames[size - 1] = "S";
			for (size_t i = 0; i < size; i++)
			{
				double temp = capacities[size - 1][i];
				capacities[size - 1][i] = capacities[index][i];
				capacities[index][i] = temp;
			}
			for (size_t i = 0; i < size; i++)
			{
				double temp = capacities[i][size - 1];
				capacities[i][size - 1] = capacities[i][index];
				capacities[i][index] = temp;
			}
		}
	}

public:
	// Default constructor: implements empty flow network
	FlowNetwork() : capacities(nullptr), vertexesNames(nullptr), size(0) {}

	// Constructor which creates a zero-defined ajecency matrix based on given vertexes
	FlowNetwork(size_t size, string* vertexesNames) : size(size)
	{
		this->vertexesNames = vertexesNames;
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++) capacities[i][j] = 0;
		}
		SwapSourceAndDrain();
	}

	// Copy constructor which returns new idendical adjecency matrix
	FlowNetwork(const FlowNetwork& copyFrom)
	{
		size = copyFrom.size;
		vertexesNames = new string[size];
		capacities = new double* [size];
		for (size_t i = 0; i < size; i++) vertexesNames[i] = copyFrom.vertexesNames[i];
		for (size_t i = 0; i < size; i++)
		{
			capacities[i] = new double[size];
			for (size_t j = 0; j < size; j++) capacities[i][j] = copyFrom.capacities[i][j];
		}
			
	}

	// Constructor for creating adjecency matrix from given components
	FlowNetwork(size_t size, string* vertexesNames, double** capacities) : capacities(capacities), vertexesNames(vertexesNames), size(size)
	{
		SwapSourceAndDrain();
	}
	
	// Destructor
	~FlowNetwork()
	{
		if (capacities != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				delete[] capacities[i];
			}
			delete[] capacities;
		}
		if (vertexesNames != nullptr) delete[] vertexesNames;
	}

	// Operator for comparing two flow networks
	friend bool operator==(FlowNetwork& gr1, FlowNetwork& gr2)
	{
		if (gr1.size != gr2.size) return false;
		for (size_t i = 0; i < gr1.size; i++) if (gr1.vertexesNames[i] != gr2.vertexesNames[i]) return false;
		for (size_t i = 0; i < gr1.size; i++)
		{
			for (size_t j = 0; j < gr1.size; j++)
			{
				if (gr1.capacities[i][j] != gr2.capacities[i][j]) return false;
			}
		}
		return true;
	}

	// Operator for input stream reading (from file)
	friend ifstream& operator>>(ifstream& stream, FlowNetwork& matrix)
	{
		string name1_buffer, name2_buffer;
		double weight;
		char st = 0;
		List<string> vertexesNames;
		while (!stream.eof())
		{
			string temp;
			stream >> name1_buffer >> name2_buffer >> weight;
			if (name1_buffer == "S")
			{
				if (st % 2 == 0) st += 1;
			}
			else if (name1_buffer == "T") throw logic_error("Drain must not have outcoming paths");
			if (name2_buffer == "T")
			{
				if ((st >> 1) % 2 == 0) st += 2;
			}
			else if (name2_buffer == "S") throw logic_error("Source must not have incoming paths");
			if (vertexesNames.Find(name1_buffer) < 0) vertexesNames.PushBack(name1_buffer);
			if (vertexesNames.Find(name2_buffer) < 0) vertexesNames.PushBack(name2_buffer);
			if (weight <= 0) throw logic_error("Capacity must be a positive value");
		}
		if (st != 3) throw logic_error("Wrong input: network has no source or/and drain");
		matrix.size = vertexesNames.GetSize();
		matrix.vertexesNames = new string [matrix.size];
		matrix.capacities = new double*[matrix.size];
		for (size_t i = 0; i < matrix.size; i++)
		{
			matrix.vertexesNames[i] = vertexesNames.GetData();
			vertexesNames.PopFront();
			matrix.capacities[i] = new double[matrix.size];
			for (size_t j = 0; j < matrix.size; j++)
			{
				matrix.capacities[i][j] = 0;
			}
		}

		stream.seekg(ios::beg);
		while (!stream.eof())
		{
			string temp;
			stream >> name1_buffer >> name2_buffer >> weight;

			size_t i = 0, j = 0, k;
			for (k = 0; k < matrix.size; k++)
			{
				if (matrix.vertexesNames[k] == name1_buffer) i = k;
				if (matrix.vertexesNames[k] == name2_buffer) j = k;
			}
			matrix.capacities[i][j] = weight;
		}

		matrix.SwapSourceAndDrain();
		return stream;
	}
	
	// Operator for pretty-printing the adjecent matrix of flow network 
	friend ostream& operator<<(ostream& stream, FlowNetwork& matrix)
	{
		size_t maxwidth = 4;
		stream << setprecision(2) << fixed;
		for (size_t i = 0; i < matrix.size; i++)
		{
			if (matrix.vertexesNames[i].length() > maxwidth) maxwidth = matrix.vertexesNames[i].length();
		}
		matrix.OutputLine(stream, matrix, maxwidth);
		stream << "| ";
		for (size_t i = 0; i < maxwidth; i++)
		{
			stream << ' ';
		}
		stream << " | ";
		for (size_t i = 0; i < matrix.size; i++)
		{
			stream << setw(matrix.vertexesNames[i].length() > maxwidth ? matrix.vertexesNames[i].length() : maxwidth)
				<< left << matrix.vertexesNames[i] << " | ";
		}
		stream << "\n";
		matrix.OutputLine(stream, matrix, maxwidth);
		for (size_t i = 0; i < matrix.size; i++)
		{
			stream << "| " << setw(maxwidth) << right << matrix.vertexesNames[i] << " | ";
			for (size_t j = 0; j < matrix.size; j++)
			{
				stream << setw(matrix.vertexesNames[i].length() > maxwidth ? matrix.vertexesNames[i].length() : maxwidth)
					<< left << matrix.capacities[i][j] << " | ";
			}
			stream << "\n";
		}
		matrix.OutputLine(stream, matrix, maxwidth);
		return stream;
	}

	// Getters (setters are missing for incapsulation)

	inline const size_t GetSize() { return size; }
	inline string* GetNames() { return vertexesNames; }
	inline double** GetValues() { return capacities; }
};
#endif // FLOWNETWORK