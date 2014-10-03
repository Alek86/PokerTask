#pragma once

namespace Logic
{
    class OptionalRank
    {
    public:
        OptionalRank()
            : m_hasValue(false)
            , m_value(Rank::Ace)
        {
        }

        void SetValue(Rank::Value data)
        {
            m_hasValue = true;
            m_value = data;
        }

        const Rank::Value* GetValue() const
        {
            if (!m_hasValue)
            {
                return nullptr;
            }

            return &m_value;
        }

    private:
        bool m_hasValue;
        Rank::Value m_value;
    };
}