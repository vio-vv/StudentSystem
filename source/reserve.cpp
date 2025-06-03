#include "student_system.hpp"

ssys::ReserveSystem::ReserveSystem() noexcept
{
    reserveBase["10"]["1"]["20"].Push("15","10"); // 预约信息
    //TODO
}

ssys::ReserveSystem::~ReserveSystem() noexcept
{
}

trm::Information ssys::ReserveSystem::CheckTime(const trm::Information& information) noexcept
{
    assert(information[0]==trm::rqs::CHECK_TIME);
    auto dateInformation=trm::ReserveDate(information[1]);
    auto reserveList=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date];//找到指定日期的预约信息
    if(!reserveList.Size())
    {
        return {trm::rpl::FAIL,trm::rpl::NO_RESERVE_EXISTS};
    }
    //待实现：只能在规定的天数内预约，比如只能预约最近一周
    trm::Information timeList;
    timeList.push_back(trm::rpl::SUCC);
    for(auto [time,reserve]:reserveList)//遍历预约信息
    {
        if(ToNum(reserve))
        {
            timeList.push_back(trm::Combine({time,reserve,ToStr(reserve)},' '));//将可预约时间加入列表
        }
    }
    return timeList; 
}

trm::Information ssys::ReserveSystem::CheckReserveTime(const trm::Information& information) noexcept
{
    assert(information[0]==trm::rqs::CHECK_RESERVE_TIME);
    auto dateInformation=trm::ReserveDate(information[1]);
    auto targetReserve=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date];//找到指定日期的预约信息
   if(targetReserve[information[2]].Exists())//检查是否存在预约信息
    {
        if(ToNum(targetReserve[information[2]]))//检查是否有可预约时间
        {
            return {trm::rpl::YES,information[1],information[2],targetReserve[information[2]]};//返回可预约时间
        }
        else
        {
            return {trm::rpl::NO,trm::rpl::NO_LEFT_RESERVE};//如果没有找到指定时间的预约信息
        }
    } 
    return {trm::rpl::NO,trm::rpl::NO_MATCH_TIME};//如果没有找到指定时间的预约信息
}

trm::Information ssys::ReserveSystem::RequestReserve(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::REQUEST_RESERVE); // Procession not matched.
    auto timeReply=SSys::Get().CheckReserveTime({trm::rqs::CHECK_RESERVE_TIME,information[1],information[2]});//检查预约时间
    if(timeReply[0]!=trm::rpl::YES)
    {
       return {trm::rpl::FAIL,timeReply[1]};
    }
    if(clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]][information[2]].Exists())
    {
        return {trm::rpl::FAIL,trm::rpl::RESERVE_EXISTS};
    }
    auto dateInformation=trm::ReserveDate(information[1]);
    auto number=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date][information[2]];
    number=ToStr(ToNum(number)-1);//将可预约数量减一
    reserveBase[dateInformation.month][dateInformation.week][dateInformation.date][information[2]] = number;
    clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]].Push(information[2], "HAVE RESERVED, READY TO USE"); // 将预约信息加入数据库//断点
    return {trm::rpl::SUCC,information[1],information[2]}; // 返回成功预约的时间和状态
    //也许会返回成功预约的时间和状态，就类似自动跳转
}

trm::Information ssys::ReserveSystem::CancelReserve(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::CANCEL_RESERVE); // Procession not matched.
    if(!clientBase[trm::IdAndPhone{information[3],information[4]}].Exists())//这个权限检查会不会太草率了
    {
       return{trm::rpl::NO_DERESERVE_ACCESS};
    }
    if(clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]][information[2]].Exists())//检查是否存在预约信息
    {
        clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]][information[2]].Clear();//清除预约信息
        if(!clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]].Size())
        {
            clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]].Remove();//清除用户预约信息
        }
        return {trm::rpl::SUCC};
    }
    else
    {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_RESERVE};
    }
}

trm::Information ssys::ReserveSystem::CheckReserveStatus(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::CHECK_RESERVE_STATUS); // Procession not matched.
    auto reserve=clientBase[trm::IdAndPhone{information[3],information[4]}][information[1]][information[2]];
    if(reserve.Exists())//检查是否存在预约信息
    {
        return {trm::rpl::SUCC,information[1],information[2],reserve};
    }
    else
    {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_RESERVE};
    }
}

trm::Information ssys::ReserveSystem::CheckReserveStatusList(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::CHECK_RESERVE_STATUS_LIST); // Procession not matched.
    trm::Information reserveList;
    reserveList.push_back(trm::rpl::SUCC);
    if(!clientBase[trm::IdAndPhone{information[1],information[2]}].Size())//检查是否存在预约信息
    {
        return {trm::rpl::FAIL,trm::rpl::NO_RESERVE_EXISTS};
    }
    for(auto [date,reserve]:clientBase[trm::IdAndPhone{information[1],information[2]}])
    {
        for(auto [time,status]:reserve)
        {
            reserveList.push_back(trm::Combine({date,time,status},'_'));//将预约信息加入列表
        }
    }
    return reserveList;
}

trm::Information ssys::ReserveSystem::AdmModifyReserveNumber(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADM_MODIFY_RESERVE_NUMBER); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADM_MODIFTY_RESERVE_NUMBER}});
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto dateInformation=trm::ReserveDate(information[3]);
    auto reserveList=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date][information[4]];//找到指定日期的预约信息
    if(!reserveList.Exists())//检查是否存在预约信息
    {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_TIME};
    }
    reserveList=information[5];//将可预约数量加入数据库
    return {trm::rpl::SUCC};
}

trm::Information ssys::ReserveSystem::AdmAddReserveTime(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADM_ADD_RESERVE_TIME); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADM_ADD_RESERVE_TIME}});
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto dateInformation=trm::ReserveDate(information[3]);
    auto reserveList=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date];//找到指定日期的预约信息
    if(reserveList[information[4]].Exists())
    {
        return {trm::rpl::FAIL,trm::rpl::TIME_HAVE_SET};
    }
    reserveList.Push(information[4],information[5]);//将可预约时间加入数据库
    return {trm::rpl::SUCC};
}

trm::Information ssys::ReserveSystem::AdmDeleteReserveTime(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADM_DELETE_RESERVE_TIME); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADM_DELETE_RESERVE_TIME}});
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto dateInformation=trm::ReserveDate(information[3]);
    auto reserveList=reserveBase[dateInformation.month][dateInformation.week][dateInformation.date];//找到指定日期的预约信息
    if(!reserveList[information[4]].Exists())//检查是否存在预约信息
    {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_TIME};
    }
    reserveList[information[4]].Clear();//清除预约时间
    if(!reserveList.Size()) // 如果没有预约时间了，清除日期
    {
        reserveBase[dateInformation.month][dateInformation.week][dateInformation.date].Remove();
    }
    return {trm::rpl::SUCC};
}

