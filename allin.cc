#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

namespace utils
{
    void AncestorMsg(int i, int j, bool awsner);

    int Min(int i, int j);

    int Min(int i, int j, int k, int l);

    int Min(int i, int j, int k, int l, int m, int n);

    int Max(int i, int j);

    /**
     * @brief Default less-than comparator
     */
    template<typename typeT>
    struct less
    {
            bool operator()(const typeT& a, const typeT& b) const
            {
                return a < b;
            }
    };

    /**
     * @brief Default greater-than comparator
     */
    template<typename typeT>
    struct greater
    {
            bool operator()(const typeT& a, const typeT& b) const
            {
                return a > b;
            }
    };

    /**
     * @brief Default equal-to comparator
     */
    template<typename typeT>
    struct equal
    {
            bool operator()(const typeT& a, const typeT& b) const
            {
                return a == b;
            }
    };

} // namespace utils

#endif // UTILS_H_
/*
 * Filename: utils.cc
 * 
 * 
 */


namespace utils
{
    void AncestorMsg(int i, int j, bool awsner)
    {
        std::cout << i << " é ancestral de " << j << " ? " << awsner << std::endl;
    }

    int Min(int i, int j)
    {
        if (i < j)
            return i;
        else
            return j;
    }

    int Min(int i, int j, int k, int l)
    {
        int min1 = utils::Min(i, j);
        int min2 = utils::Max(k, l);

        return utils::Min(min1, min2);
    }

    int Min(int i, int j, int k, int l, int m, int n)
    {
        int min1 = utils::Min(i, j, k, l);
        int min2 = utils::Min(m, n);

        return utils::Min(min1, min2);
    }

    int Max(int i, int j)
    {
        if (i > j)
            return i;
        else
            return j;
    }
} // namespace utils
/*
 * Filename: vector.h
 * 
 * 
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>


// The growth factor determines how much a vector should grow when it needs to
// be resized
#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_START_SIZE 8

/**
 * @brief A dynamic array-based vector class
 *
 * This class provides dynamic array functionality for storing and managing elements
 * of type 'typeT'. It allows for insertion, deletion, and various operations on
 * the elements in the vector
 *
 * @tparam typeT The type of elements stored in the vector
 *
 * TODO implement functions: insert(pos, value), erase(pos)
 */
template<typename typeT>
class Vector
{
    private:
        // Pointer to first element of vector (array)
        typeT* m_elements;
        // Total space used by vector, including elements and free space
        std::size_t m_capacity;
        // Num of elements in vector
        std::size_t m_size;

    public:
        /**
         * @brief Default constructor
         */
        Vector();

        /**
         * @brief Constructor
         * @param size Initial space allocated for the vector
         */
        Vector(const std::size_t size);

        /**
         * @brief Constructor
         * @param size Initial space allocated for the vector
         * @param value Initialization value for the elements in the vector
         */
        Vector(const std::size_t size, const typeT value);

        /**
         * @brief Construtor with initializer list to receive data as {x1, x2, x3,
         *..., xn}
         **/
        Vector(const std::initializer_list<typeT> values);

        /**
         * @brief Destructor
         */
        ~Vector();

        /**
         * @brief Copy constructor
         **/
        Vector(const Vector<typeT>& other);

        /**
         * @brief Assignment operator
         **/
        Vector& operator=(const Vector<typeT>& other);

        /**
         * @brief Overload do operador []
         * @param index Índice do elemento que será buscado
         * @return Elemento na posição index
         */
        typeT& operator[](const std::size_t index);
        const typeT& operator[](const std::size_t index) const;

        /**
         * @brief Operator overload for ==
         * @param other Vector to be used for comparison
         * @return True if they are equal, False otherwise
         */
        bool operator==(Vector<typeT>& other);

        /**
         * @brief Get the current size of the vector
         * @return An integer representing the size of the vector
         */
        std::size_t Size() const;

        /**
         * @brief Get the current maximum size (when this limit is reached, the vector
         * is reallocated to accommodate more elements)
         * @return An integer representing the current maximum size of the vector
         */
        std::size_t GetMaxSize() const;

        /**
         * @brief Check if the vector is empty
         * @return True if the vector is empty, False otherwise
         */
        bool IsEmpty() const;

        /**
         * @brief Swap the positions of two elements
         * @param index1, index2 Positions of the elements to be swapped
         * @throw std::out_of_range If any of the indices is invalid
         */
        void Swap(const std::size_t index1, const std::size_t index2);

        /**
         * @brief Insert a new element at the end of the vector
         * @param element New element
         */
        void PushBack(const typeT element);

        /**
         * @brief Remove the element at the end of the vector
         */
        void PopBack();

        /**
         * @return The element at the beginning of the vector
         * @throw std::overflow_error If the vector is empty
         */
        typeT& Front() const;

        /**
         * @return The element at the end of the vector
         * @throw std::overflow_error If the vector is empty
         */
        typeT& Back() const;

        /**
         * @brief Clear the vector
         */
        void Clear();

        /**
         * @brief Resize the vector
         * @param newSize New size of the vector
         * @param val Default value for custom values when resizing
         */
        void Resize(const std::size_t newSize, const typeT val = typeT());

        /**
         * @brief Allocate a new space for this vector
         * @param newalloc Size of the new allocate
         **/
        void Reserve(const std::size_t newalloc);

        /**
         * @return The element at the specified index
         * @throw std::out_of_range If the index is invalid
         **/
        typeT& At(const std::size_t index);
        const typeT& At(const std::size_t index) const;

        // Iterator
        using value_type = typeT;
        using pointer    = typeT*;
        using reference  = typeT&;

        typedef struct Iterator
        {
            public:
                Iterator(pointer ptr)
                    : m_ptr(ptr)
                { }

                Iterator() { }

                reference operator*() const
                {
                    return *m_ptr;
                }

                pointer operator->()
                {
                    return m_ptr;
                }

                Iterator& operator++()
                {
                    m_ptr++;
                    return *this;
                }

                Iterator operator++(int)
                {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                friend bool operator==(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr == b.m_ptr;
                };

                friend bool operator!=(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr != b.m_ptr;
                };

            private:
                pointer m_ptr;

        } Iterator;

        Iterator begin()
        {
            return Iterator(&m_elements[0]);
        }

        Iterator end()
        {
            return Iterator(&m_elements[m_size]);
        }
};

template<typename typeT>
Vector<typeT>::Vector()
{
    this->m_capacity = VECTOR_START_SIZE;
    this->m_size     = 0;
    this->m_elements = new typeT[this->m_capacity];
}

template<typename typeT>
Vector<typeT>::Vector(const std::size_t size)
{
    this->m_capacity = size;
    this->m_size     = 0;
    this->m_elements = new typeT[this->m_capacity];
}

template<typename typeT>
Vector<typeT>::Vector(const std::size_t size, const typeT val)
{
    this->m_capacity = size;
    this->m_size     = size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < size; i++)
    {
        this->m_elements[i] = val;
    }
}

template<typename typeT>
Vector<typeT>::Vector(const std::initializer_list<typeT> values)
{
    this->m_elements = new typeT[values.size()];
    this->m_capacity = values.size();
    this->m_size     = values.size();

    std::copy(values.begin(), values.end(), m_elements);
}

template<typename typeT>
Vector<typeT>::~Vector()
{
    delete[] this->m_elements;
}

template<typename typeT>
Vector<typeT>::Vector(const Vector<typeT>& other)
{
    this->m_capacity = other.m_capacity;
    this->m_size     = other.m_size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < this->m_size; i++)
        this->m_elements[i] = other.m_elements[i];
}

template<typename typeT>
Vector<typeT>& Vector<typeT>::operator=(const Vector<typeT>& other)
{
    if (this == &other)
        return *this;

    delete[] this->m_elements;

    this->m_capacity = other.m_capacity;
    this->m_size     = other.m_size;
    this->m_elements = new typeT[this->m_capacity];

    for (std::size_t i = 0; i < this->m_size; i++)
        this->m_elements[i] = other.m_elements[i];

    return *this;
}

template<typename typeT>
typeT& Vector<typeT>::operator[](const std::size_t index)
{
    return this->m_elements[index];
}

template<typename typeT>
const typeT& Vector<typeT>::operator[](const std::size_t index) const
{
    return this->m_elements[index];
}

template<typename typeT>
bool Vector<typeT>::operator==(Vector<typeT>& other)
{
    if (this->m_size != other.Size())
        return false;

    for (std::size_t i = 0; i < this->m_size; i++)
    {
        if (this->m_elements[i] != other[i])
        {
            return false;
        }
    }

    return true;
}

template<typename typeT>
std::size_t Vector<typeT>::Size() const
{
    return this->m_size;
}

template<typename typeT>
std::size_t Vector<typeT>::GetMaxSize() const
{
    return this->m_capacity;
}

template<typename typeT>
bool Vector<typeT>::IsEmpty() const
{
    return this->m_size == 0;
}

template<typename typeT>
void Vector<typeT>::Swap(const std::size_t index1, const std::size_t index2)
{
    if ((std::size_t)utils::Max(index1, index2) > this->m_capacity)
        throw std::out_of_range("Index out of bounds");

    typeT aux = this->m_elements[index1];

    this->m_elements[index1] = this->m_elements[index2];
    this->m_elements[index2] = aux;
}

template<typename typeT>
void Vector<typeT>::PushBack(const typeT element)
{
    if (this->m_size == this->m_capacity)
    {
        this->Reserve(this->m_capacity * VECTOR_GROWTH_FACTOR);
    }

    this->m_elements[this->m_size++] = element;
}


template<typename typeT>
typeT& Vector<typeT>::Front() const
{
    if (this->IsEmpty())
        throw std::overflow_error("Vector is empty");

    return m_elements[0];
}

template<typename typeT>
typeT& Vector<typeT>::Back() const
{
    if (this->IsEmpty())
        throw std::overflow_error("Vector is empty");

    return m_elements[this->m_size - 1];
}

template<typename typeT>
void Vector<typeT>::PopBack()
{
    if (not this->IsEmpty())
    {
        this->m_size--;
    }
}

template<typename typeT>
void Vector<typeT>::Clear()
{
    this->m_size = 0;
}

template<typename typeT>
void Vector<typeT>::Resize(std::size_t newSize, typeT val)
{
    this->Reserve(newSize);

    for (std::size_t i = this->m_size; i < newSize; ++i)
    {
        this->m_elements[i] = val;
    }

    this->m_size = newSize;
}

template<typename typeT>
void Vector<typeT>::Reserve(std::size_t newAlloc)
{

    if (newAlloc <= this->m_capacity)
        return;

    typeT* newElements = new typeT[newAlloc]();

    std::size_t i;
    for (i = 0; i < this->m_size; i++)
    {
        newElements[i] = this->m_elements[i];
    }

    delete[] this->m_elements;
    this->m_elements = newElements;
    this->m_capacity = newAlloc;
}

template<typename typeT>
typeT& Vector<typeT>::At(std::size_t index)
{
    if (index > this->m_size)
        throw std::out_of_range("Index out of bounds");

    return this->m_elements[index];
}

template<typename typeT>
const typeT& Vector<typeT>::At(std::size_t index) const
{
    if (index > this->m_size)
        throw std::out_of_range("Index out of bounds");

    return this->m_elements[index];
}


#endif // VECTOR_H_
/*
 * Filename: vector.cc
 * 
 * 
 */

/*
 * Filename: trick.h
 * 
 * 
 */

#ifndef TRICK_H_
#define TRICK_H_

#include <cstdint>

/**
 * @brief Class representing a skateboarding trick with associated score and execution
 * time
 */
class Trick
{
    private:
        int32_t  m_score;         ///< Trick's score
        uint32_t m_executionTime; ///< Trick's execution time

    public:
        /**
         * @brief Default constructor for the Trick class
         */
        Trick();

        /**
         * @brief Constructor for the Trick class
         * @param score The score of this trick
         * @param execTime The execution time of this trick
         */
        Trick(int32_t score, uint32_t execTime);

        /**
         * @brief Destructor for the Trick class
         */
        ~Trick();

        /**
         * @brief Set the score for the trick.
         * @param score The score value to be set
         */
        void SetScore(int32_t score);

        /**
         * @brief Set the execution time for the trick
         * @param execTime The execution time value to be set
         */
        void SetExecutionTime(uint32_t execTime);

        /**
         * @brief Get the score of the trick
         * @return The score of the trick
         */
        int32_t GetScore();

        /**
         * @brief Get the execution time of the trick
         * @return The execution time of the trick in seconds
         */
        uint32_t GetExecutionTime();
};

#endif // TRICK_H_
/*
 * Filename: trick.cc
 * 
 * 
 */


Trick::Trick()
{
    this->m_score = this->m_executionTime = 0;
}

Trick::Trick(int32_t score, uint32_t execTime)
{
    this->m_score         = score;
    this->m_executionTime = execTime;
}

Trick::~Trick() { }

void Trick::SetScore(int32_t score)
{
    this->m_score = score;
}

void Trick::SetExecutionTime(uint32_t execTime)
{
    this->m_executionTime = execTime;
}

int32_t Trick::GetScore()
{
    return this->m_score;
}

uint32_t Trick::GetExecutionTime()
{
    return this->m_executionTime;
}
/*
 * Filename: skatepark_section.h
 * 
 * 
 */

#ifndef SKATEPARK_SECTION_H_
#define SKATEPARK_SECTION_H_

#include <cstdint>

/**
 * @brief Class representing a section in a skatepark with bonus and traversal time
 */
class Section
{
    private:
        uint16_t m_bonus;         ///< Bonus associated with the section
        uint32_t m_traversalTime; ///< Traversal time for the section

    public:
        /**
         * @brief Default constructor for the Section class
         */
        Section();

        /**
         * @brief Parameterized constructor for the Section class
         * @param bonus Bonus value for the section
         * @param traversalTime Traversal time for the section in seconds
         */
        Section(int16_t bonus, uint32_t traversalTime);

        /**
         * @brief Destructor for the Section class
         */
        ~Section();

        /**
         * @brief Set the bonus for the section
         * @param bonus Bonus value to be set
         */
        void SetBonus(uint16_t bonus);

        /**
         * @brief Set the traversal time for the section
         * @param traversalTime Traversal time value to be set
         */
        void SetTraversalTime(uint32_t traversalTime);

        /**
         * @brief Get the bonus of the section
         * @return The bonus of the section
         */
        int16_t GetBonus();

        /**
         * @brief Get the traversal time of the section
         * @return The traversal time of the section in seconds
         */
        uint32_t GetTraversalTime();
};

#endif // SKATEPARK_SECTION_H_
/*
 * Filename: skatepark_section.cc
 * 
 * 
 */


Section::Section()
{
    this->m_bonus = this->m_traversalTime = 0;
}

Section::Section(int16_t bonus, uint32_t traversalTime)
{
    this->m_bonus         = bonus;
    this->m_traversalTime = traversalTime;
}

Section::~Section() { }

void Section::SetBonus(uint16_t bonus)
{
    this->m_bonus = bonus;
}

void Section::SetTraversalTime(uint32_t traversalTime)
{
    this->m_traversalTime = traversalTime;
}

int16_t Section::GetBonus()
{
    return this->m_bonus;
}

uint32_t Section::GetTraversalTime()
{
    return this->m_traversalTime;
}
/*
 * Filename: skatepark.h
 * 
 * 
 */

#ifndef SKATEPARK_H_
#define SKATEPARK_H_

#include <cmath>
#include <cstdint>
#include <limits>


constexpr uint16_t MAX_TRICKS   = 1e1;
constexpr uint16_t MAX_SECTIONS = 1e2;

constexpr int64_t NEGATIVE_INFINITY = std::numeric_limits<int64_t>::min();
const uint16_t    COMBINATIONS      = std::pow(2, MAX_TRICKS);

constexpr uint16_t BIT_MASK_ONE = 0x0001; // 0000000000000001

/**
 * @brief Class representing a Skate Park with tricks, sections, and a memoization table
 * for optimization
 */
class SkatePark
{
    private:
        Vector<Trick>   m_tricks;   ///< Vector of tricks in the skate park
        Vector<Section> m_sections; ///< Vector of sections in the skate park

        // Memoization tables for dynamic programming optimization
        Vector<Vector<int64_t>> m_score; ///< Given that we performed trick i, what
                                         ///< score does trick j have
        Vector<Vector<int64_t>>
            m_mostRadicalTrick; ///< Memoization table used in the search for the set of
                                ///< tricks in each section that will yield the most
                                ///< points

        Vector<Vector<uint16_t>>
            m_trickPermutations; ///< The set of trick i contains which tricks

        Vector<int64_t>
            m_trickDurations; ///< Stores the total duration of the set of tricks i

        // Set of tricks performed in each section
        Vector<Vector<uint16_t>> m_tricksPerSections;

        /**
         * @brief Given that we performed the trick set 'previousTrick' in the previous
         *section, how many points can we achieve by performing the 'currentTrick' set?
         * @param currentTrick Trick set we intend to perform now
         * @param previousTrick Trick set we performed in the previous section
         *
         * NOTE: In case of repetition of tricks performed in the previous section,
         *       the score in the current section will be halved
         **/
        void StoreScore(uint16_t currentTrick, uint16_t previousTrick);

        /**
         * @brief Applies dynamic programming to find the highest score
         *        we can achieve in the skate park
         * @param section Section considered in the current calculation
         * @param trickSet Trick set we intend to perform in this section
         * @return Maximum possible score in the current section
         **/
        int64_t FindMostRadicalTrick(uint16_t section, uint16_t trickSet);

        /**
         * @brief Generates and stores the permutation of tricks
         **/
        void GenerateTrickPermutations();

        /**
         * @brief Given the trick set, stores the time required to perform it
         * @param trickSet Trick set for which the duration will be calculated
         **/
        void StoreTrickDuration(uint16_t trickSet);

        /**
         * @brief Given the section and the trick set, determines if this trick set
         *        can be performed within the maximum travel time of the section
         * @param section Section considered in the calculation
         * @param trickSet Trick set considered in the calculation
         **/
        bool IsTimeWithinSectionLimit(uint16_t section, uint16_t trickSet);

    public:
        /**
         * @brief Default constructor for the SkatePark class
         */
        SkatePark();

        /**
         * @brief Destructor for the SkatePark class
         */
        ~SkatePark();

        /**
         * @brief Adds a new trick to the skate park
         * @param trickScore The score of the trick to be added
         * @param trickExecTime The execution time of the trick to be added
         */
        void AddTrick(int32_t trickScore, uint32_t trickExecTime);

        /**
         * @brief Adds a new section to the skate park
         * @param sectionBonus The bonus of the section to be added
         * @param sectionTraversalTime The traversal time of the section to be added
         */
        void AddSection(uint16_t sectionBonus, uint32_t sectionTraversalTime);

        /**
         * @brief Employs dynamic programming to find the most badass trick that can be
         *        performed on this skate park.
         * @return The score of the most badass trick.
         **/
        int64_t FindMostFuckingRadicalTrick();

        /**
         * @brief Prints the set of tricks that were performed in each section.
         **/
        void ShowTricksList();

        /**
         * @brief Prints the matrices on the screen for debugging purposes.
         **/
        void DumpMatrices();
};

#endif // SKATEPARK_H_
/*
 * Filename: skatepark.cc
 *
 * 
 */


SkatePark::SkatePark()
{
    // Initialize vectors and matrices
    this->m_score.Resize(COMBINATIONS,
                         Vector<int64_t>(COMBINATIONS, NEGATIVE_INFINITY));

    this->m_mostRadicalTrick.Resize(MAX_SECTIONS,
                                    Vector<int64_t>(COMBINATIONS, NEGATIVE_INFINITY));

    this->m_tricksPerSections.Resize(MAX_SECTIONS, Vector<uint16_t>(COMBINATIONS, 0));
    this->m_trickPermutations.Resize(COMBINATIONS, Vector<uint16_t>());
    this->m_trickDurations.Resize(COMBINATIONS, NEGATIVE_INFINITY);
}

SkatePark::~SkatePark() { }

void SkatePark::AddTrick(int32_t trickScore, uint32_t trickExecTime)
{
    this->m_tricks.PushBack(Trick(trickScore, trickExecTime));
}

void SkatePark::AddSection(uint16_t sectionBonus, uint32_t sectionTraversalTime)
{
    this->m_sections.PushBack(Section(sectionBonus, sectionTraversalTime));
}

void SkatePark::StoreScore(uint16_t currentTrick, uint16_t previousTrick)
{
    uint16_t repeated = currentTrick & previousTrick;
    int64_t  points   = 0;

    for (uint16_t i = 0; i < MAX_TRICKS; i++)
    {
        if (repeated >> i & BIT_MASK_ONE)
        {
            points += this->m_tricks[i].GetScore() / 2;
        }
        else if (currentTrick >> i & BIT_MASK_ONE)
        {
            points += this->m_tricks[i].GetScore();
        }
    }

    this->m_score[currentTrick][previousTrick] = points;
}

bool SkatePark::IsTimeWithinSectionLimit(uint16_t section, uint16_t trickSet)
{
    uint32_t sectionTime = this->m_sections[section].GetTraversalTime();

    if (this->m_trickDurations[trickSet] != NEGATIVE_INFINITY)
    {
        return this->m_trickDurations[trickSet] <= sectionTime;
    }

    int64_t trickSetTime = 0;

    for (uint16_t i = 0; i < MAX_TRICKS; i++)
    {
        if (trickSet >> i & BIT_MASK_ONE)
        {
            trickSetTime += this->m_tricks[i].GetExecutionTime();
        }
    }

    this->m_trickDurations[trickSet] = trickSetTime;

    return trickSetTime <= sectionTime;
}

void SkatePark::GenerateTrickPermutations()
{
    for (uint16_t i = 0; i < std::pow(2, this->m_tricks.Size()); i++)
    {
        for (uint16_t j = 0; j < MAX_TRICKS; j++)
        {
            if (i >> j & BIT_MASK_ONE)
            {
                this->m_trickPermutations[i].PushBack(j);
            }
        }
    }
}

int64_t SkatePark::FindMostRadicalTrick(uint16_t section, uint16_t trickSet)
{
    // Base case: No more sections
    if (section > this->m_sections.Size() - 1)
    {
        return 0;
    }

    // If the value has already been calculated, use the one stored in the table instead
    if (this->m_mostRadicalTrick[section][trickSet] != NEGATIVE_INFINITY)
    {
        return this->m_mostRadicalTrick[section][trickSet];
    }

    int64_t max              = NEGATIVE_INFINITY;
    int16_t mostRadicalTrick = 0;

    int64_t  aux;
    uint16_t numTricksInThisSection;

    for (uint16_t i = 0; i < COMBINATIONS; i++)
    {
        // Check if the trick set 'i' can be performed in section 'section'
        if (not IsTimeWithinSectionLimit(section, i))
            continue;

        // Check if the score for the trick set 'i' given that we performed the trick
        // 'trickSet' in the previous section has already been calculated
        if (this->m_score[i][trickSet] == NEGATIVE_INFINITY)
        {
            StoreScore(i, trickSet);
        }

        numTricksInThisSection = this->m_trickPermutations[i].Size();

        aux = FindMostRadicalTrick(section + 1, i) +
              this->m_score[i][trickSet] * this->m_sections[section].GetBonus() *
                  numTricksInThisSection;

        if (aux > max)
        {
            max              = aux;
            mostRadicalTrick = i;
        }
    }

    // Store the most radical trick set for this section
    this->m_tricksPerSections[section][trickSet] = mostRadicalTrick;
    this->m_mostRadicalTrick[section][trickSet]  = max;

    return this->m_mostRadicalTrick[section][trickSet];
}

int64_t SkatePark::FindMostFuckingRadicalTrick()
{
    GenerateTrickPermutations();

    FindMostRadicalTrick(0, 0);

    return this->m_mostRadicalTrick[0][0];
}

void SkatePark::ShowTricksList()
{
    uint16_t    spell = 0;
    uint16_t    aux;
    std::string set;

    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        spell = this->m_tricksPerSections[i][spell];

        aux = 0;
        set.clear();

        for (uint16_t j = 0; j < MAX_TRICKS; j++)
        {
            if (spell >> j & BIT_MASK_ONE)
            {
                aux++;
                set += std::to_string(j + 1) + " ";
            }
        }
        std::cout << aux << " " << set.substr(0, set.size() - 1) << std::endl;
    }
}

void SkatePark::DumpMatrices()
{

    std::cout << "\n## Points Matrix (m x m') ##" << std::endl;

    for (std::size_t i = 0; i < COMBINATIONS; i++)
    {
        if (this->m_score[i][0] == NEGATIVE_INFINITY)
            break;
        std::cout << i << " | ";
        for (std::size_t j = 0; j < COMBINATIONS; j++)
        {
            if (this->m_score[i][j] == NEGATIVE_INFINITY)
                break;

            std::cout << this->m_score[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "## Score (sections x m')" << std::endl;
    for (std::size_t i = 0; i < this->m_sections.Size(); i++)
    {
        if (this->m_mostRadicalTrick[i][0] == NEGATIVE_INFINITY)
            break;

        std::cout << i << " | ";
        for (std::size_t j = 0; j < COMBINATIONS; j++)
        {
            if (this->m_mostRadicalTrick[i][j] == NEGATIVE_INFINITY)
                break;

            std::cout << this->m_mostRadicalTrick[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
/*
 * Filename: main.cc
 * 
 * 
 */

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>


int main()
{
    uint16_t numSections, numTricks, sectionBonus;
    uint32_t sectionTraversalTime, trickExecutionTime;
    int32_t  trickScore;

    std::cin >> numSections >> numTricks;

    SkatePark sk8Park;

    for (std::size_t i = 0; i < numSections; i++)
    {
        std::cin >> sectionBonus >> sectionTraversalTime;
        sk8Park.AddSection(sectionBonus, sectionTraversalTime);
    }

    for (std::size_t i = 0; i < numTricks; i++)
    {
        std::cin >> trickScore >> trickExecutionTime;
        sk8Park.AddTrick(trickScore, trickExecutionTime);
    }

    std::cout << sk8Park.FindMostFuckingRadicalTrick() << std::endl;
    sk8Park.ShowTricksList();

    return EXIT_SUCCESS;
}
