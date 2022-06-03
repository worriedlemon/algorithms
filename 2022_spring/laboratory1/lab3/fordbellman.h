#include "linear.h"
#include <fstream>
#include <iomanip>

#define INF ((double)(1e300 * 1e300))

const string NOT_AVAILABLE = "N/A";

class AdjMatrix
{
	size_t size;
	string* names;
	double** values;

	void outputline(ostream& stream, AdjMatrix& matrix, size_t maxwidth)
	{
		stream << "--";
		for (size_t i = 0; i < maxwidth; i++) stream << '-';
		stream << "---";
		for (size_t i = 0; i < matrix.size; i++)
		{
			const size_t len = matrix.names[i].length();
			for (size_t j = 0; j < len; j++)
			{
				stream << '-';
			}
			stream << "--" << (i == matrix.size - 1 ? '\n' : '-');
		}
	}

public:
	AdjMatrix() : values(nullptr), names(nullptr), size(0) {}
	AdjMatrix(size_t size, string* names, double** values) : values(values), names(names), size(size) {}
	~AdjMatrix()
	{
		if (values != nullptr)
		{
			for (size_t i = 0; i < size; i++)
			{
				delete[] values[i];
			}
			delete[] values;
		}
	}

	friend bool operator==(AdjMatrix& gr1, AdjMatrix& gr2)
	{
		if (gr1.size != gr2.size) return false;
		for (size_t i = 0; i < gr1.size; i++) if (gr1.names[i] != gr2.names[i]) return false;
		for (size_t i = 0; i < gr1.size; i++)
		{
			for (size_t j = 0; j < gr1.size; j++)
			{
				if (gr1.values[i][j] != gr2.values[i][j]) return false;
			}
		}
		return true;
	}

	friend ifstream& operator>>(ifstream& stream, AdjMatrix& matrix)
	{
		string name1_buffer, name2_buffer;
		double value1_buffer, value2_buffer;
		List<string> names;
		while (!stream.eof())
		{
			string temp;
			stream >> name1_buffer >> name2_buffer >> value1_buffer >> value2_buffer;
			if (names.Find(name1_buffer) < 0) names.PushBack(name1_buffer);
			if (names.Find(name2_buffer) < 0) names.PushBack(name2_buffer);
			if (value1_buffer == 0)
			{
				stream.clear();
				stream >> temp >> value2_buffer;
			}
			if (value2_buffer == 0)
			{
				stream.clear();
				if (temp == NOT_AVAILABLE) throw invalid_argument("Wrong input");
				stream >> temp;
			}
		}
		matrix.size = names.GetSize();
		matrix.names = new string [matrix.size];
		matrix.values = new double*[matrix.size];
		for (size_t i = 0; i < matrix.size; i++)
		{
			matrix.names[i] = names.GetData();
			names.PopFront();
			matrix.values[i] = new double[matrix.size];
			for (size_t j = 0; j < matrix.size; j++)
			{
				matrix.values[i][j] = (i == j ? 0 : INF);
			}
		}

		stream.seekg(ios::beg);
		while (!stream.eof())
		{
			string temp;
			stream >> name1_buffer >> name2_buffer >> value1_buffer >> value2_buffer;
			if (value1_buffer == 0)
			{
				stream.clear();
				stream >> temp >> value2_buffer;
				value1_buffer = INF;
			}
			if (value2_buffer == 0)
			{
				stream.clear();
				stream >> temp;
				value2_buffer = INF;
			}

			size_t i = 0, j = 0, k;
			for (k = 0; k < matrix.size; k++)
			{
				if (matrix.names[k] == name1_buffer) i = k;
				if (matrix.names[k] == name2_buffer) j = k;
			}
			matrix.values[i][j] = value1_buffer;
			matrix.values[j][i] = value2_buffer;
		}
		return stream;
	}

	friend ostream& operator<<(ostream& stream, AdjMatrix& matrix)
	{
		size_t maxwidth = 0;
		for (size_t i = 0; i < matrix.size; i++)
		{
			if (matrix.names[i].length() > maxwidth) maxwidth = matrix.names[i].length();
		}
		matrix.outputline(stream, matrix, maxwidth);
		stream << "| ";
		for (size_t i = 0; i < maxwidth; i++)
		{
			stream << ' ';
		}
		stream << " | ";
		for (size_t i = 0; i < matrix.size; i++)
		{
			stream << setw(matrix.names[i].length()) << left << matrix.names[i] << " | ";
		}
		stream << "\n";
		matrix.outputline(stream, matrix, maxwidth);
		for (size_t i = 0; i < matrix.size; i++)
		{
			stream << "| " << setw(maxwidth) << right << matrix.names[i] << " | ";
			for (size_t j = 0; j < matrix.size; j++)
			{
				stream << setw(matrix.names[j].length()) << left << matrix.values[i][j] << " | ";
			}
			stream << "\n";
		}
		matrix.outputline(stream, matrix, maxwidth);
		return stream;
	}

	AdjMatrix& FordBellman()
	{
		if (size == 0) throw logic_error("Adjecent matrix does not have a graph yet");
		AdjMatrix* newMatrix = new AdjMatrix();
		newMatrix->size = size;
		newMatrix->names = names;
		newMatrix->values = new double* [size];
		
		// Choosing the vertex to calculate from
		for (size_t vertex = 0; vertex < size; vertex++)
		{
			// Initializing array with 0 on a current vertex and +INF on other vertexes
			double* distances = new double[size];
			for (size_t i = 0; i < size; i++)
			{
				distances[i] = (i == vertex ? 0 : INF);
			}

			// Repeating algorithm [vertex count - 1] times (enough)
			for (size_t step = 0; step < size; step++)
			{
				// Relaxing edges
				for (size_t i = 0; i < size; i++)
				{
					for (size_t j = 0; j < size; j++)
					{
						if (i != j && values[i][j] < INF && distances[i] + values[i][j] < distances[j])
						{
							if (step == size - 1) throw logic_error("Graph has negative cycles");
							else distances[j] = distances[i] + values[i][j];
						}
					}
				}
			}
			newMatrix->values[vertex] = distances;
		}

		return *newMatrix;
	}

	inline double** GetValues() { return values; }
};