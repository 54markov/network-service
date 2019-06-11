#pragma once

#include <data-protocol/i-data.hpp>
#include <cpu-monitor/cpu-monitor.hpp>

#include <vector>
#include <memory>

/******************************************************************************/
/* Data procotol organization^                                                */
/*  iData interface                                                           */
/*        |                                                                   */
/* { key: value } <- DataObject                                               */
/*          |                                                                 */
/*          +- DataObject                                                     */
/*          +- DataString                                                     */
/*          +- DataArray                                                      */
/*                |                                                           */
/*                +- DataObject                                               */
/*                +- DataString                                               */
/*                +- DataArray -> [ *,*,* ]                                   */
/******************************************************************************/
class DataProtocol
{
    public:
        DataProtocol() = default;
        ~DataProtocol() = default;

        void build(std::vector<CpuData>& v);

        std::string serialize();
        void print();

        void deserialize(std::string string);

        std::string find(std::string& key);

    private:
        std::unique_ptr<IData> data_;

        std::vector<std::string> split_(std::string s, const std::string& delimiter);
        std::unique_ptr<IData> parse_(std::string string);
        std::unique_ptr<IData> parseObject_(std::string string);
        std::unique_ptr<IData> parseArray_(std::string string);
};
