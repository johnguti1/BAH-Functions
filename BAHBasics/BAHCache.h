#if !defined(BAHCHACHE_H)
#define BAHCHACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <stdexcept>
#include <any>
#include <type_traits>

TString TStringSpacer(const TString& input, int width, const TString& align = "L") {
    int inputLength = input.Length();
    if (width <= inputLength) {
        return input;  // Return original if longer than desired width
    }
    int totalPadding = width - inputLength;
    if (align == "L") {  // Left align
        return input + TString(' ', totalPadding);
    } 
    else if (align == "R") {  // Right align
        return TString(' ', totalPadding) + input;
    } 
    else if (align == "C") {  // Center align
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;
        return TString(' ', leftPadding) + input + TString(' ', rightPadding);
    }
    return input + TString(' ', totalPadding);  // Default to left align
}
 
//==========================================================================
// List of BAHCaching class functions:
//---------------------------
// Constructor/Destructor:
//  - BAHCache(T&& filename)          // Constructor with templated filename
//  - ~BAHCache()                     // Destructor
//---------------------------
// Cache Operations:
//  - void cache(const TString& key, const T& input)                           // Main template
//  - void cache(const TString& key, std::initializer_list<double> list)      // For numbers
//  - void cache(const TString& key, std::initializer_list<const char*> list) // For strings
//  - void cache(const TString& key, std::initializer_list<std::pair<...>>)   // For pairs
//---------------------------
// Basic Get Operations:
//  - double getDouble(const TString& key)
//  - int getInt(const TString& key)
//  - TString getTString(const TString& key)
//---------------------------
// Vector Get Operations:
//  - std::vector<double> getVecDouble(const TString& key)
//  - std::vector<TString> getVecTString(const TString& key)
//  - double getVecEleDouble(const TString& key, size_t index)
//  - TString getVecEleTString(const TString& key, size_t index)
//---------------------------
// Pair Vector Get Operations:
//  - std::vector<std::pair<TString, double>> getPVecDouble(const TString& key)
//  - std::vector<std::pair<TString, TString>> getPVecTString(const TString& key)
//  - double getPVecEleDouble(const TString& key, size_t index)
//  - double getPVecEleDouble(const TString& key, const TString& pairKey)
//  - TString getPVecEleTString(const TString& key, size_t index)
//  - TString getPVecEleTString(const TString& key, const TString& pairKey)
//---------------------------
// Cache Information:
//  - bool isKeyPresent(const TString& key)
//  - bool isKeyOfType(const TString& key, ValueType expectedType)
//  - ValueType getKeyType(const TString& key)
//---------------------------
// Display Functions:
//  - void printKeyInfo(const TString& key, bool showType, bool showKey, bool showValue)
//  - void printFullCache()
//  - void printKeysContaining(const TString& pattern)
//---------------------------
// Cache Control:
//  - void clearKey(const TString& key)
//  - void clearCache()
//  - void resetCache()
//  - void setOverwrite(bool allowOverwriting)
//  - void setSpacing(size_t spacing)
//  - size_t getSpacing() const
//---------------------------
// File Operations:
//  - void saveCacheToFile()
//  - void loadCacheFromFile()
//---------------------------
// Supported Types:
//  - int
//  - double
//  - float     [defaults to doubles]
//  - long      [defaults to doubles]
//  - TString   [with automatic conversion from const char*, string, char[N]]
//  - vector<double>
//  - vector<TString>
//  - pair<TString, double>
//  - pair<TString, TString>
//  - vector<pair<TString, double>>
//  - vector<pair<TString, TString>>
//  - Initializer lists for all vector types
//  - Initializer lists for pairs with string literals
//==========================================================================



//==========================================================================
//==========================================================================
class BAHCache {
private:
    // Member variables
    bool m_overwrite = true;
    size_t m_entriesSinceLastSave = 0;
    size_t m_spacingSize = 20;
    const size_t m_saveFrequency = 20;
    std::string m_cacheFileName;

    // Define enum first
    enum class ValueType : int {
        INT,
        DOUBLE,
        TSTRING,
        VEC_DOUBLE,
        VEC_TSTRING,
        PAIR_TSTRING_DOUBLE,
        VEC_PAIR_TSTRING_DOUBLE,
        PAIR_TSTRING_TSTRING,
        VEC_PAIR_TSTRING_TSTRING
    };

    // Then forward declarations
    template<typename T> struct CacheTraits;
    template<typename T, ValueType V> struct TrivialCacheTraits;
    template<typename T1, typename T2, ValueType V> struct PairCacheTraits;
    template<typename T, ValueType V> struct VectorCacheTraits;
    //==========================================================================


    // Basic cache info for each key
    struct KeyInfo {
        bool exists;
        ValueType type;
        bool typeMatches;
    };
    //==========================================================================
    KeyInfo getKeyInfo(const TString& key, ValueType expectedType = ValueType::INT) {
        auto it = m_cache.find(key);
        if (it == m_cache.end()) {
            return {false, ValueType::INT, false};
        }
        return {
            true, 
            it->second.first, 
            it->second.first == expectedType
        };
    }
    //==========================================================================
    void checkTypeConflict(const TString& key, ValueType newType) {
        auto info = getKeyInfo(key, newType);
        if (info.exists && !info.typeMatches) {
            std::cerr << "Warning: Key '" << key << "' already exists with type " 
                     << ValTypeToTStr(info.type) << std::endl;
            std::cerr << "         Overwriting with type " 
                     << ValTypeToTStr(newType) << std::endl;
        }
    }
    //==========================================================================
    
    // For Triggering cache save every N entries
    void cacheSaveTrigger() {
        ++m_entriesSinceLastSave;
        if (m_entriesSinceLastSave >= m_saveFrequency) {
            saveCacheToFile();
            m_entriesSinceLastSave = 0;
        }
    }
    //==========================================================================

    // Helper for vector serialization and deserialization
    template<typename T>
    static std::vector<char> serializeVector(const std::vector<T>& vec) {
        std::vector<char> buffer;
        size_t count = vec.size();
        // Serialize vector size
        buffer.insert(buffer.end(), 
            reinterpret_cast<char*>(&count), 
            reinterpret_cast<char*>(&count) + sizeof(count));
        if constexpr (std::is_trivially_copyable_v<T>) {
            // For types like double that can be directly copied
            buffer.insert(buffer.end(),
                reinterpret_cast<const char*>(vec.data()),
                reinterpret_cast<const char*>(vec.data() + vec.size()));
        } else {
            // For complex types like TString, include size for each element
            for (const auto& elem : vec) {
                auto elemData = CacheTraits<T>::serialize(elem);
                size_t elemSize = elemData.size();
                // Add element size
                buffer.insert(buffer.end(),
                    reinterpret_cast<char*>(&elemSize),
                    reinterpret_cast<char*>(&elemSize) + sizeof(elemSize));
                    
                // Add element data
                buffer.insert(buffer.end(), elemData.begin(), elemData.end());
            }
        }
        return buffer;
    }
    template<typename T>
    static std::vector<T> deserializeVector(const std::vector<char>& data) {
        std::vector<T> result;
        size_t pos = 0;
        // Check if data is large enough to contain size
        if (data.size() < sizeof(size_t)) {
            throw std::runtime_error("Corrupted data: too small to contain vector size");
        }
        size_t count;
        std::memcpy(&count, &data[pos], sizeof(count));
        pos += sizeof(count);
    
        // Basic size validation
        if (count > std::vector<T>().max_size()) {
            throw std::runtime_error("Invalid vector size in deserialization");
        }
        result.reserve(count);
        if constexpr (std::is_trivially_copyable_v<T>) {
            // For trivially copyable types, check exact size
            if (data.size() - pos < count * sizeof(T)) {
                throw std::runtime_error("Corrupted data: insufficient data for vector elements");
            }
            result.resize(count);
            std::memcpy(result.data(), &data[pos], count * sizeof(T));
        } else {
            // For complex types, just ensure we have some data left
            if (data.size() <= pos) {
                throw std::runtime_error("Corrupted data: no data for vector elements");
            }
            // Process each element individually
            for (size_t i = 0; i < count; ++i) {
                if (data.size() - pos < sizeof(size_t)) {
                    throw std::runtime_error("Corrupted data: insufficient data for element size");
                }
                size_t elemSize;
                std::memcpy(&elemSize, &data[pos], sizeof(elemSize));
                pos += sizeof(elemSize);
                
                if (data.size() - pos < elemSize) {
                    throw std::runtime_error("Corrupted data: insufficient data for element");
                }
                std::vector<char> elemData(data.begin() + pos, 
                                         data.begin() + pos + elemSize);
                result.push_back(CacheTraits<T>::deserialize(elemData));
                pos += elemSize;
            }
        }
        return result;
    }
    //==========================================================================

    // Helper for pair serialization and deserialization
    template<typename T1, typename T2>
    static std::vector<char> serializePair(const std::pair<T1, T2>& pair) {
        std::vector<char> buffer;
        
        // Serialize first element
        auto firstData = CacheTraits<T1>::serialize(pair.first);
        size_t firstSize = firstData.size();
        buffer.insert(buffer.end(), 
            reinterpret_cast<char*>(&firstSize), 
            reinterpret_cast<char*>(&firstSize) + sizeof(firstSize));
        buffer.insert(buffer.end(), firstData.begin(), firstData.end());
        
        // Serialize second element
        auto secondData = CacheTraits<T2>::serialize(pair.second);
        size_t secondSize = secondData.size();
        buffer.insert(buffer.end(), 
            reinterpret_cast<char*>(&secondSize), 
            reinterpret_cast<char*>(&secondSize) + sizeof(secondSize));
        buffer.insert(buffer.end(), secondData.begin(), secondData.end());
        
        return buffer;
    }
    template<typename T1, typename T2>
    static std::pair<T1, T2> deserializePair(const std::vector<char>& data) {
        size_t pos = 0;
        // Deserialize first element
        size_t firstSize;
        std::memcpy(&firstSize, &data[pos], sizeof(firstSize));
        pos += sizeof(firstSize);
        std::vector<char> firstData(data.begin() + pos, data.begin() + pos + firstSize);
        T1 first = CacheTraits<T1>::deserialize(firstData);
        pos += firstSize;
        // Deserialize second element
        size_t secondSize;
        std::memcpy(&secondSize, &data[pos], sizeof(secondSize));
        pos += sizeof(secondSize);
        std::vector<char> secondData(data.begin() + pos, data.begin() + pos + secondSize);
        T2 second = CacheTraits<T2>::deserialize(secondData);
        return std::make_pair(first, second);
    }
    //==========================================================================

    // General Template for CacheTraits
    template<typename T>
    struct CacheTraits {
        static constexpr bool is_supported = false;
        static constexpr ValueType type = ValueType::INT;
        static std::vector<char> serialize(const T& value) {
            throw std::runtime_error("Unsupported type for serialization");
        }
        static T deserialize(const std::vector<char>& data) {
            throw std::runtime_error("Unsupported type for deserialization");
        }
    };
    //==========================================================================  

    // Helper template for trivially copyable types (int, double)
    template<typename T>
    struct NumericCacheTraits {
        static constexpr bool is_supported = std::is_arithmetic_v<T>;
        static constexpr ValueType type = std::is_integral_v<T> ? ValueType::INT : ValueType::DOUBLE;
        
        static std::vector<char> serialize(const T& value) {
            std::vector<char> buffer(sizeof(T));
            std::memcpy(buffer.data(), &value, sizeof(T));
            return buffer;
        }
        
        static T deserialize(const std::vector<char>& data) {
            T value;
            std::memcpy(&value, data.data(), sizeof(T));
            return value;
        }
    };
    // integer and double specializations using helpers    
    template<> struct CacheTraits<int> : NumericCacheTraits<int> {};
    template<> struct CacheTraits<double> : NumericCacheTraits<double> {};
    template<> struct CacheTraits<float> : NumericCacheTraits<float> {};
    template<> struct CacheTraits<long> : NumericCacheTraits<long> {};
    //==========================================================================  
    
    // Helper template for string-like types that convert to TString
    template<typename T>
    struct StringLikeCacheTraits {
        static constexpr bool is_supported = true;
        static constexpr ValueType type = ValueType::TSTRING;
        static std::vector<char> serialize(const T& value) {
            TString tstr(value);  // Convert to TString first
            std::string str(tstr.Data());
            return std::vector<char>(str.begin(), str.end());
        }
        static TString deserialize(const std::vector<char>& data) {
            return TString(data.data(), data.size());
        }
    };
    // String type specializations using helper
    template<> struct CacheTraits<TString> : StringLikeCacheTraits<TString> {};
    template<> struct CacheTraits<const char*> : StringLikeCacheTraits<const char*> {};
    template<> struct CacheTraits<std::string> : StringLikeCacheTraits<std::string> {};
    template<size_t N> struct CacheTraits<char[N]> : StringLikeCacheTraits<char[N]> {};
    //==========================================================================
    
    // Helper template for pair types
    template<typename T1, typename T2, ValueType V>
    struct PairCacheTraits {
        static constexpr bool is_supported = true;
        static constexpr ValueType type = V;
        static std::vector<char> serialize(const std::pair<T1, T2>& pair) {
            return serializePair(pair);
        }
        static std::pair<T1, T2> deserialize(const std::vector<char>& data) {
            return deserializePair<T1, T2>(data);
        }
    };

    // Helper template for string pair types that convert to TString pairs
    template<typename T1, typename T2>
    struct StringPairCacheTraits {
        static constexpr bool is_supported = true;
        static constexpr ValueType type = ValueType::PAIR_TSTRING_TSTRING;
        // Helper to convert any string-like type to TString
        static TString toTString(const auto& value) {
            if constexpr (std::is_same_v<std::decay_t<decltype(value)>, TString>) {
                return value;
            } else {
                return TString(value);
            }
        }
        static std::vector<char> serialize(const std::pair<T1, T2>& pair) {
            return serializePair(std::make_pair(
                toTString(pair.first), 
                toTString(pair.second)
            ));
        }
        static std::pair<TString, TString> deserialize(const std::vector<char>& data) {
            return deserializePair<TString, TString>(data);
        }
    };

    // Pair specializations
    template<> struct CacheTraits<std::pair<TString, double>> 
        : PairCacheTraits<TString, double, ValueType::PAIR_TSTRING_DOUBLE> {};
    // String pair specializations using helper
    template<> struct CacheTraits<std::pair<TString, TString>> 
        : StringPairCacheTraits<TString, TString> {};
    template<> struct CacheTraits<std::pair<const char*, const char*>> 
        : StringPairCacheTraits<const char*, const char*> {};
    template<> struct CacheTraits<std::pair<std::string, std::string>> 
        : StringPairCacheTraits<std::string, std::string> {};
    template<size_t N1, size_t N2> struct CacheTraits<std::pair<char[N1], char[N2]>> 
        : StringPairCacheTraits<char[N1], char[N2]> {};
    //==========================================================================  
    

    // Helper template for vector types
    template<typename T, ValueType V>
    struct VectorCacheTraits {
        static constexpr bool is_supported = true;
        static constexpr ValueType type = V;
        static std::vector<char> serialize(const std::vector<T>& vec) {
            return serializeVector(vec);
        }
        static std::vector<T> deserialize(const std::vector<char>& data) {
            return deserializeVector<T>(data);
        }
    };
    // Vector specializations using helper
    template<> struct CacheTraits<std::vector<double>> 
        : VectorCacheTraits<double, ValueType::VEC_DOUBLE> {};
    template<> struct CacheTraits<std::vector<TString>> 
        : VectorCacheTraits<TString, ValueType::VEC_TSTRING> {};
    // Vector-Pair specializations using helpers
    template<> struct CacheTraits<std::vector<std::pair<TString, double>>> 
        : VectorCacheTraits<std::pair<TString, double>, ValueType::VEC_PAIR_TSTRING_DOUBLE> {};  
    template<> struct CacheTraits<std::vector<std::pair<TString, TString>>> 
        : VectorCacheTraits<std::pair<TString, TString>, ValueType::VEC_PAIR_TSTRING_TSTRING> {};
    //==========================================================================  

    // Helper template for initializer lists
    template<typename T>
    struct InitListCacheTraits {
        static constexpr bool is_supported = true;
        
        // Type deduction based on content type
        static constexpr ValueType type = []() {
            if constexpr (std::is_arithmetic_v<T>) {
                return std::is_integral_v<T> ? ValueType::INT : ValueType::DOUBLE;
            } else if constexpr (std::is_convertible_v<T, const char*>) {
                return ValueType::VEC_TSTRING;
            } else {
                return ValueType::INT; // default, should never be reached
            }
        }();
        
        static std::vector<char> serialize(const std::initializer_list<T>& list) {
            if constexpr (std::is_arithmetic_v<T>) {
                return serializeVector(std::vector<T>(list.begin(), list.end()));
            } else if constexpr (std::is_convertible_v<T, const char*>) {
                std::vector<TString> converted;
                converted.reserve(list.size());
                for (const auto& str : list) {
                    converted.push_back(TString(str));
                }
                return serializeVector(converted);
            }
        }
    };
    //========================================================================== 

    // Helper for pair initializer lists
    template<typename T1, typename T2>
    struct PairInitListCacheTraits {
        static constexpr bool is_supported = true;
        static constexpr ValueType type = ValueType::VEC_PAIR_TSTRING_DOUBLE;
        
        static std::vector<char> serialize(const std::initializer_list<std::pair<T1, T2>>& list) {
            std::vector<std::pair<TString, double>> converted;
            converted.reserve(list.size());
            for (const auto& p : list) {
                converted.push_back({TString(p.first), p.second});
            }
            return serializeVector(converted);
        }
    };
    // Specializations using the helpers
    template<typename T>
    struct CacheTraits<std::initializer_list<T>> : InitListCacheTraits<T> {};
    template<>
    struct CacheTraits<std::initializer_list<std::pair<const char*, double>>> 
        : PairInitListCacheTraits<const char*, double> {};
    template<>
    struct CacheTraits<std::initializer_list<std::pair<const char* const, double>>> 
        : PairInitListCacheTraits<const char* const, double> {};
    //==========================================================================

    // Helper functions using the unified traits
    //==========================================================================
    template<typename T>
    std::vector<char> serialize(const T& value) {
        return CacheTraits<T>::serialize(value);
    }
    //==========================================================================
    template<typename T>
    T deserialize(const std::vector<char>& data) {
        return CacheTraits<T>::deserialize(data);
    }
    //==========================================================================
    
    // Generally useful functions [next to public function level]
    //==========================================================================
    TString ValTypeToTStr(ValueType type) {
        switch (type) {
            case ValueType::INT:
                return "int";
            case ValueType::DOUBLE:
                return "double";
            case ValueType::TSTRING:
                return "TString";
            case ValueType::VEC_DOUBLE:
                return "vec<double>";
            case ValueType::VEC_TSTRING:
                return "vec<TString>";
            case ValueType::VEC_PAIR_TSTRING_DOUBLE:
                return "vec<pair(TStr,doub)>";
            case ValueType::PAIR_TSTRING_TSTRING:
                return "pair(TStr,TStr)";
            case ValueType::VEC_PAIR_TSTRING_TSTRING:
                return "vec<pair(TStr,TStr)>";
            default:
                return "Unkown_ValueType";
        }
    }
    //==========================================================================
    template<typename T1, typename T2>
    TString formatPair(const std::pair<T1, T2>& p) {
        TString first, second;
        // Handle first element
        if constexpr (std::is_floating_point_v<T1>) {
            first = TString::Format("%.6g", p.first);
        } else {
            first = TString(p.first);
        }
        // Handle second element
        if constexpr (std::is_floating_point_v<T2>) {
            second = TString::Format("%.6g", p.second);
        } else {
            second = TString(p.second);
        }
        return TString::Format("(%s, %s)", first.Data(), second.Data());
    }
    //==========================================================================
    template<typename T>
    TString formatVector(const std::vector<T>& vec) {
        TString result = "{ ";
        for (size_t i = 0; i < vec.size(); ++i) {
            if constexpr (std::is_same_v<T, double>) {
                result += TString::Format("%.6g", vec[i]);
            }
            else if constexpr (std::is_same_v<T, TString>) {
                result += vec[i];
            }
            else {
                result += TString(vec[i]);
            }
            
            if (i < vec.size() - 1) {
                result += ", ";
            }
        }
        result += " }";
        return result;
    }
    //==========================================================================
    template<typename T1, typename T2>
    TString formatVectorPairs(const std::vector<std::pair<T1, T2>>& vec) {
        TString result = "{ ";
        for (size_t i = 0; i < vec.size(); ++i) {
            result += formatPair(vec[i]);
            if (i < vec.size() - 1) result += ", ";
        }
        result += " }";
        return result;
    }
    //==========================================================================

    // Template helper for when adding items to the cache
    template<typename T>
    void cacheValue(const TString& inputKey, const T& input, ValueType type) {
        if (isKeyPresent(inputKey)) {
            if (!m_overwrite) {
                std::cout << "Warning: Key '" << inputKey << "' already exists. Skipping." << std::endl;
                return;
            }
            checkTypeConflict(inputKey, type);
        }
        m_cache[inputKey] = {type, serialize(input)};
        if (++m_entriesSinceLastSave >= m_saveFrequency) {
            saveCacheToFile();
            m_entriesSinceLastSave = 0;
        }
    }
    //==========================================================================


    // Helper function for printing a single entry based on the input
    void printCacheValue(const TString& key) {
        auto it = m_cache.find(key);
        if (it == m_cache.end()) {
            std::cout << "<not found>";
            return;
        }
        const auto& [type, data] = it->second;
        switch (type) {
            case ValueType::INT:
                std::cout << deserialize<int>(data);
                break;
            case ValueType::DOUBLE:
                std::cout << deserialize<double>(data);
                break;
            case ValueType::TSTRING:
                std::cout << deserialize<TString>(data);
                break;
            case ValueType::VEC_DOUBLE:
                std::cout << formatVector(deserialize<std::vector<double>>(data));
                break;
            case ValueType::VEC_TSTRING:
                std::cout << formatVector(deserialize<std::vector<TString>>(data));
                break;
            case ValueType::VEC_PAIR_TSTRING_DOUBLE:
                std::cout << formatVectorPairs(deserialize<std::vector<std::pair<TString, double>>>(data));
                break;
            case ValueType::VEC_PAIR_TSTRING_TSTRING:
                std::cout << formatVectorPairs(deserialize<std::vector<std::pair<TString, TString>>>(data));
                break;
            default:
                std::cout << "<unknown type>";
                break;
        }
    }
    // Helper function for printing a single entry based on the input
    void printCacheEntry(const TString& key, ValueType type, bool showType = true, bool showKey = true, bool showValue = true) {
        if (showType) {
            std::cout << "Type=" << TStringSpacer(ValTypeToTStr(type), m_spacingSize, "L");
        }
        if (showKey) {
            if (showType) std::cout << ", ";
            std::cout << "Key=" << TStringSpacer(key, m_spacingSize, "L");
        }
        if (showValue) {
            if (showType || showKey) std::cout << ", ";
            std::cout << "Value= ";
            printCacheValue(key);
        }
        std::cout << std::endl;
    }
    // Helper function for sorting the map/cache before printing parts or all of it
    auto getSortedCache(const TString& pattern = "") const {
        std::map<ValueType, std::vector<std::pair<TString, std::pair<ValueType, std::vector<char>>>>> sortedCache;
        // Filter and sort entries
        for (const auto& item : m_cache) {
            if (pattern.IsNull() || item.first.Contains(pattern)) {
                sortedCache[item.second.first].push_back({item.first, item.second});
            }
        }
        // Sort entries within each type group
        for (auto& [type, entries] : sortedCache) {
            std::sort(entries.begin(), entries.end(),
                [](const auto& a, const auto& b) { return a.first < b.first; });
        }
        return sortedCache;
    }
    // Helper function for printing from the cache
    void printCacheContents(const std::map<ValueType, std::vector<std::pair<TString, std::pair<ValueType, std::vector<char>>>>>& sortedCache, const TString& header) {
        if (sortedCache.empty()) {
            std::cout << "No entries to display" << std::endl;
            return;
        }
        std::cout << "------ " << header << " ------" << std::endl;
        for (const auto& typeGroup : sortedCache) {
            for (const auto& entry : typeGroup.second) {
                printCacheEntry(entry.first, entry.second.first);
            }
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    //==========================================================================


public:    

    // Structs for TString Hashing and Equality
    struct TStringHash {
        std::size_t operator()(const TString& str) const {
            return std::hash<std::string>()(std::string(str.Data()));
        }
    };
    //==========================================================================
    struct TStringEqual {
        bool operator()(const TString& lhs, const TString& rhs) const {
            return lhs == rhs;
        }
    };
    //==========================================================================

    // Stores: key -> (type, raw bytes) [Here because it requires The Hash and Equal]
    std::unordered_map<TString, std::pair<BAHCache::ValueType, std::vector<char>>, TStringHash, TStringEqual> m_cache;
    //==========================================================================

    // Constructor and Destructor
    template<typename T>
    BAHCache(T&& filename) 
        : m_cacheFileName(std::is_same_v<std::decay_t<T>, TString> 
            ? std::string(filename.Data())  // Inline conversion
            : std::forward<T>(filename)) {
        loadCacheFromFile();
    }
    //==========================================================================
    ~BAHCache() {
        if (m_entriesSinceLastSave > 0) {
            saveCacheToFile();
        }
    }
    //==========================================================================
    
    
    //==========================================================================
    void setSpacing(size_t spacing) {
        m_spacingSize = spacing;
    }
    size_t getSpacing() const {
        return m_spacingSize;
    }
    //==========================================================================


    // Add/retrieve to/from cache
    template<typename T>    // Single unified cache function
    void cache(const TString& inputKey, const T& input) {
        static_assert(CacheTraits<T>::is_supported, "Unsupported type for caching");     
        cacheValue(inputKey, input, CacheTraits<T>::type);
    }
    // Overload for numeric initializer lists
    void cache(const TString& inputKey, std::initializer_list<double> list) {
        cache(inputKey, std::vector<double>(list));
    }
    // Overload for pair initializer lists
    void cache(const TString& inputKey, std::initializer_list<std::pair<const char*, double>> list) {
        std::vector<std::pair<TString, double>> converted;
        converted.reserve(list.size());
        for (const auto& p : list) {
            converted.emplace_back(TString(p.first), p.second);
        }
        cache(inputKey, converted);
    }
    // Overload for string literal initializer lists
    void cache(const TString& inputKey, std::initializer_list<const char*> list) {
        std::vector<TString> converted;
        converted.reserve(list.size());
        for (const auto& str : list) {
            converted.emplace_back(TString(str));
        }
        cache(inputKey, converted);
    }
    // Overload for paired string literal initializer lists 
    void cache(const TString& inputKey, std::initializer_list<std::pair<const char*, const char*>> list) {
        std::vector<std::pair<TString, TString>> converted;
        converted.reserve(list.size());
        for (const auto& p : list) {
            converted.emplace_back(TString(p.first), TString(p.second));
        }
        cache(inputKey, converted);
    }
    
    
    //==========================================================================
    template <typename T>  // Generic get function (for all types)
    T get(const TString& inputKey) {
        auto it = m_cache.find(inputKey);
        if (it == m_cache.end()) {
            throw std::runtime_error("Key not found in cache");
        }
        const auto& [type, data] = it->second;
        if (type != CacheTraits<T>::type) {
            throw std::runtime_error("Type mismatch");
        }
        return deserialize<T>(data);
    }
    //==========================================================================

    // Helper template for getting vector of pairs
    template<typename T>
    std::vector<std::pair<TString, T>> getVecPairs(const TString& key, ValueType expectedType) {
        auto it = m_cache.find(key);
        if (it == m_cache.end()) {
            throw std::runtime_error("Key not found in cache");
        }
        if (it->second.first != expectedType) {
            throw std::runtime_error("Type mismatch: expected vector of pairs");
        }
        return get<std::vector<std::pair<TString, T>>>(key);
    }
    // Helper template for getting pair value by index
    template<typename T>
    T getVecPairByIndex(const TString& key, size_t index, ValueType expectedType) {
        auto pairs = getVecPairs<T>(key, expectedType);
        if (index >= pairs.size()) {
            throw std::runtime_error("Index out of range");
        }
        return pairs[index].second;
    }
    // Helper template for getting pair value by key
    template<typename T>
    T getVecPairByKey(const TString& key, const TString& pairKey, ValueType expectedType) {
        auto pairs = getVecPairs<T>(key, expectedType);
        for (const auto& pair : pairs) {
            if (pair.first == pairKey) {
                return pair.second;
            }
        }
        throw std::runtime_error("Pair key not found: " + std::string(pairKey.Data()));
    }
    //==========================================================================

 

    // Specific get functions for common types
    double getDouble(const TString& key) {
        return get<double>(key);
    }
    int getInt(const TString& key) {
        return get<int>(key);
    }
    TString getTString(const TString& key) {
        return get<TString>(key);
    }
    std::vector<double> getVecDouble(const TString& key) {
        return get<std::vector<double>>(key);
    }
    std::vector<TString> getVecTString(const TString& key) {
        return get<std::vector<TString>>(key);
    }
    
    // Get double from vector by index  [might be useful in looping]
    double getVecEleDouble(const TString& key, size_t index) {
        auto vec = getVecDouble(key);
        if (index >= vec.size()) {
            throw std::runtime_error("Index out of range");
        }
        return vec[index];
    }
    // Get TString from vector by index
    TString getVecEleTString(const TString& key, size_t index) {
        auto vec = getVecTString(key);
        if (index >= vec.size()) {
            throw std::runtime_error("Index out of range");
        }
        return vec[index];
    }
    //==========================================================================

    // Base function that gets the full vector of pairs (TString, double)
    std::vector<std::pair<TString, double>> getPVecDouble(const TString& key) {
        return getVecPairs<double>(key, ValueType::VEC_PAIR_TSTRING_DOUBLE);
    }
    // Get double value by key and index 
    double getPVecEleDouble(const TString& key, size_t index) {
        return getVecPairByIndex<double>(key, index, ValueType::VEC_PAIR_TSTRING_DOUBLE);
    }
    // Get double value by key and pairkey
    double getPVecEleDouble(const TString& key, const TString& pairKey) {
        return getVecPairByKey<double>(key, pairKey, ValueType::VEC_PAIR_TSTRING_DOUBLE);
    }
    //==========================================================================

    // Base function that gets the full vector of pairs (TString, TString)
    std::vector<std::pair<TString, TString>> getPVecTString(const TString& key) {
        return getVecPairs<TString>(key, ValueType::VEC_PAIR_TSTRING_TSTRING);
    }
    // Get TString value by key and index 
    TString getPVecEleTString(const TString& key, size_t index) {
        return getVecPairByIndex<TString>(key, index, ValueType::VEC_PAIR_TSTRING_TSTRING);
    }
    // Get TString value by key and pairkey
    TString getPVecEleTString(const TString& key, const TString& pairKey) {
        return getVecPairByKey<TString>(key, pairKey, ValueType::VEC_PAIR_TSTRING_TSTRING);
    }
    //==========================================================================

    //  File I/O 
    void saveCacheToFile() {
        //std::cout << "Attempting to save cache to " << m_cacheFileName << std::endl;
        std::ofstream outFile(m_cacheFileName, std::ios::binary);
        for (const auto& [key, val] : m_cache) {
            std::string keyStr = key.Data();
            size_t keyLen = keyStr.length();
            outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
            outFile.write(keyStr.c_str(), keyLen);
            ValueType type = val.first;
            outFile.write(reinterpret_cast<const char*>(&type), sizeof(type));
            size_t dataSize = val.second.size();
            outFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
            outFile.write(val.second.data(), dataSize);
        }
        outFile.close();
        std::cout << "Cache saved to " << m_cacheFileName << std::endl;
    }
    //==========================================================================
    void loadCacheFromFile() {
        std::ifstream inFile(m_cacheFileName, std::ios::binary);
        if (!inFile) {
            std::cerr << "--------------------------------" << std::endl;
            std::cerr << "Failed to open file for reading!" << std::endl;
            std::cerr << "--------------------------------" << std::endl;
            return;
        }
        while (inFile) {
            size_t keyLength;
            inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
            if (inFile.eof()) break;
            std::string keyStr(keyLength, '\0');
            inFile.read(&keyStr[0], keyLength);
            TString key(keyStr.c_str()); // recreate TString key
            ValueType type;
            inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
            size_t dataSize;
            inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
            std::vector<char> valueData(dataSize);
            inFile.read(valueData.data(), dataSize);
            m_cache[key] = {type, valueData};
        }
        inFile.close();
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Cache loaded from " << m_cacheFileName << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
    //==========================================================================
    // To check if key is in cache
    bool isKeyPresent(const TString& key) {
        return getKeyInfo(key).exists;
    }
    // Add a method to check if key exists with specific type
    bool isKeyOfType(const TString& key, ValueType expectedType) {
        auto info = getKeyInfo(key, expectedType);
        return info.exists && info.typeMatches;
    }
    // To retrieve the type
    ValueType getKeyType(const TString& key) {
        auto info = getKeyInfo(key);
        if (!info.exists) {
            throw std::runtime_error("Key not found in cache");
        }
        return info.type;
    }
    //==========================================================================
    void clearKey(const TString& key) {
        if (isKeyPresent(key)) {
            m_cache.erase(key);
            std::cout << "Cleared key: " << key << std::endl;
        } else {
            std::cout << "Key not found: " << key << std::endl;
        }
    }
    //==========================================================================
    //==========================================================================

    // Cache-wide functions
    //==========================================================================
    void clearCache() {
        m_cache.clear();
        m_entriesSinceLastSave = 0;
        std::cout << "Cache cleared" << std::endl;
    }
    // Reset cache to initial state (clear and delete file)
    void resetCache() {
        clearCache();
        if (std::remove(m_cacheFileName.c_str()) == 0) {
            std::cout << "Cache file deleted: " << m_cacheFileName << std::endl;
        } else {
            std::cerr << "Error deleting cache file: " << m_cacheFileName << std::endl;
        }
    }
    //  To allow for overwriteing keys already in cache
    void setOverwrite(bool allowOverwriting) {
        m_overwrite = allowOverwriting;
    }
    

    // Use printKeyInfo to use common implementation
    void printKeyInfo(const TString& key, bool showType = true, bool showKey = true, bool showValue = true) {
        auto it = m_cache.find(key);
        if (it == m_cache.end()) {
            std::cout << "Key not found: " << key << std::endl;
            return;
        }
        printCacheEntry(key, it->second.first, showType, showKey, showValue);
    }
    // Print all entries in the cache
    void printFullCache() {
        printCacheContents(getSortedCache(), "Cache Contents for " + m_cacheFileName);
    }
    // Print all entries with Keys containing the input specific pattern
    void printKeysContaining(const TString& pattern) {
        printCacheContents(getSortedCache(pattern), "Cache Keys Containing '" + pattern + "'");
    }
    //==========================================================================
    //==========================================================================
};


// Example usage
int Test_BAHCache() {
    TString testfile = "test_dir/cache.dat";
    BAHCache cache(testfile);
    // Test basic types
    cache.cache("int_test", 42);
    cache.cache("double_test", 3.14159);
    cache.cache("string_test", TString("Hello"));
    // Test vector types
    cache.cache("vec_double", std::vector<double>{1.1, 2.2, 3.3});
    cache.cache("vec_string", std::vector<TString>{"a", "b", "c"});
    // Test pair types
    cache.cache("pairs", std::vector<std::pair<TString, double>>{
        {"x", 1.0}, {"y", 2.0}
    });
    // Test TString pairs
    cache.cache("string_pair", std::make_pair(TString("key"), TString("value")));
    cache.cache("string_pairs", std::vector<std::pair<TString, TString>>{
        {TString("key1"), TString("value1")},
        {TString("key2"), TString("value2")}
    });

    
    cache.cache("string_test2", "Hello, crap");
    cache.cache("vec_TString1", {"Hello", "crap"});
    cache.cache("vec_double2", {1.1, 2.2, 3.3, 5.5, 6.6, 7.7, 8.8, 9.9});
    cache.cache("string_pair2", std::make_pair("key","value"));

    cache.cache("vec_pairs1", {
        std::make_pair("chic0", 1.1), 
        std::make_pair("chic1", 2.2), 
        std::make_pair("chic2", 3.3)
    });
    
    // Or with brace initialization
    cache.cache("vec_pairs2", {
        {"chic0", 10.1032}, 
        {"chic1", 2.2}, 
        {"chic2", 3.3}
    });
    
    // Or with explicit vector construction
    cache.cache("vec_pairs3", std::vector<std::pair<TString, double>>{
        {"chic0", 10.1032}, 
        {"chic1", 2.2}, 
        {"chic2", 3.3}
    });



    // Test in your Test_BAHCache function:
    cache.cache("string_pairs_test", {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    });
    
    // Or with make_pair
    cache.cache("string_pairs_test2", {
        std::make_pair("key1", "value1"),
        std::make_pair("key2", "value2"),
        std::make_pair("key3", "value3")
    });
    
    // Or with explicit vector construction
    cache.cache("string_pairs_test3", std::vector<std::pair<TString, TString>>{
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    });
    
    // By index  [usiongg depreciated functions]
    //double val1 = cache.getDoubleVecPair("vec_pairs1", 0);  // gets first double value
    //TString str1 = cache.getTStringVecPair("string_pairs", 0);  // gets first string value
    // By key  [usiongg depreciated functions]
    //double val2 = cache.getDoubleVecPair("vec_pairs1", "chic0");  // gets value for "chic0"
    //TString str2 = cache.getTStringVecPair("string_pairs", "key1");  // gets value for "key1"

    cache.printFullCache();

    //cout << val1 << "   " << val2 << endl;
    //cout << str1 << "   " << str2 << endl;
    return 0;
}




#endif