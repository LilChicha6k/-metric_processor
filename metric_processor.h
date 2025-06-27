#pragma once
#include <optional>

//Collects and calculates basic statistics for numeric data streams:
//- Count of values
//- Sum of values
//- Minimum value
//- Maximum value
//- Average value
//T Numeric type (int, float, double, etc.)

template<typename T>
class MetricProcessor
{
private:
	size_t m_count{};
	T m_sum{};
	std::optional<T> m_min;
	std::optional<T> m_max;

public:
	MetricProcessor() { m_count = 0; m_sum = T{}; m_min = std::nullopt; m_max = std::nullopt; }

	//Add value and update min,max,sum,count
	void add_value(T&& value)
	{
		++m_count;
		m_sum += std::move(value);

		if (!m_min || value < *m_min)
			m_min = value;
		if (!m_max || value > *m_max)
			m_max = value;
	}

	//Number of values
	const size_t count() const { return m_count; }

	//Sum of all values
	const T sum() const { return m_sum; }

	//Reset all collected metrics
	void reset()
	{
		m_count = 0;
		m_sum = T{};
		m_min.reset();
		m_max.reset();
	}

	std::optional<T> min() const { return m_min; }

	std::optional<T> max() const { return m_max; }

	//Average value or std::nullopt if no data
	std::optional<double> avg() const
	{
		if (has_data())
			return static_cast<double>(m_sum) / m_count;
		else
			return std::nullopt;
	}

	//true if any data has been
	bool has_data() const { return m_count > 0; }
};