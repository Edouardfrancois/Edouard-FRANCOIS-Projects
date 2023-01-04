/*
** EPITECH PROJECT, 2022
** server
** File description:
** ManageQueu
*/

#ifndef MANAGEQUEU_HPP_
#define MANAGEQUEU_HPP_

#include <queue>
#include <vector>
#include <uuid/uuid.h>
#include <condition_variable>
#include <mutex>
#include <exception>

#include "Serveur.hpp"
#include "ThreadPool/utils/SafeQueue.hpp"

#if __APPLE__
#define MSG_CONFIRM 0
#endif

template <typename DataType>
class OnePacketQueue
{
public:
    /**
     * @brief Construct a new One Packet Queue object
     *
     */
    OnePacketQueue(){};
    /**
     * @brief Construct a new One Packet Queue object
     *
     * @param Data the data to put
     * @param e information about the socket event
     */
    OnePacketQueue(DataType Data, Networks::SocketEvent_u &e) : Data(Data), e(e){};
    /**
     * @brief Set the Urs Id object
     *
     * @param NewGameId
     */
    void SetUrsId(size_t &NewGameId)
    {
        this->GameUsrId = GameUsrId;
    }
    /**
     * @brief Destroy the One Packet Queue object
     *
     */
    ~OnePacketQueue() = default;
    DataType Data;
    size_t GameUsrId;
    Networks::SocketEvent_u e;
};

class Uuid
{
public:
    /**
     * @brief Construct a new Uuid object
     *
     */
    Uuid(){};
    /**
     * @brief Construct a new Uuid object
     *
     * @param Newuuid Uuid To Copy
     */
    Uuid(const uuid_t &Newuuid)
    {
        uuid_copy(uuid, Newuuid);
    };
    /**
     * @brief Construct a new Uuid object
     *
     * @param Newuuid New uuid
     * @param addr the addr struct of the client
     */
    Uuid(uuid_t &Newuuid, const struct sockaddr_in &addr) : sockaddr(addr)
    {
        uuid_copy(uuid, Newuuid);
    }
    /**
     * @brief Compy a Uuid to a new uuid
     *
     * @param NewUuid the new uuid
     * @return uuid_t& the curent uuid
     */
    uuid_t &operator=(uuid_t &NewUuid)
    {
        uuid_copy(NewUuid, uuid);
        return uuid;
    }
    /**
     * @brief Destroy the Uuid object
     *
     */
    ~Uuid() = default;
    uuid_t uuid;
    struct sockaddr_in sockaddr;
};

/**
 * @brief
 *
 * @tparam DataType the type of the packet
 */
template <typename DataType>
class OneQueu
{
public:
    /**
     * @brief Construct a new One Queu object
     *
     * @param UuidOfLobby the uuid of the lobby
     */
    OneQueu(uuid_t UuidOfLobby)
    {
        uuid_copy(this->_UuidOfLobby, UuidOfLobby);
        uuid_unparse_lower(UuidOfLobby, this->_StrLobbyUuid);
        this->Cv = std::make_shared<std::condition_variable>();
    }
    /**
     * @brief Destroy the One Queu object
     *
     */
    ~OneQueu() = default;

    /**
     * @brief check if this uuid is in this queue
     *
     * @param uuid the uuid the the usr
     * @param addr the addr struct if the user
     * @return >=1 find wive addr and usr is in this queue
     * @return -1 find wive the uuid and usr is in this queue
     * @return 0 not found
     */
    int IsUuidInThisQueue(const uuid_t &uuid, const struct sockaddr_in &addr) const
    {
        size_t index = 0;
        for (const auto &usr : this->_UuidInThisQueu)
        {
            if (usr.sockaddr.sin_port == addr.sin_port)
                return index + 1;
            ++index;
        }
        for (const auto &usr : this->_UuidInThisQueu)
        {
            if (uuid_compare(uuid, usr.uuid) == 0)
                return -1;
        }
        return false;
    }

    /**
     * @brief Get the Uuid By Uuid T object
     *
     * @param uuid the uuid od the usr
     * @return Uuid& the Uuid class object of the uuid
     */
    Uuid &GetUuidByUuidT(const uuid_t &uuid)
    {
        for (auto &usr : this->_UuidInThisQueu)
        {
            if (uuid_compare(uuid, usr.uuid) == 0)
                return usr;
        }
        throw std::runtime_error("Uuid not found");
    }

    /**
     * @brief Put data on the queue if the uuid usr is on this queue
     *
     * @param p the data to put
     * @param uuid the uuid of the usr
     * @param e the socket event struct of the client
     * @return true the data is put
     * @return false the use is not on this queue
     */
    bool PutDataOnQueueIfUuidThreadIsEgal(DataType &p, const uuid_t &uuid, Networks::SocketEvent_u &e)
    {
        int index = IsUuidInThisQueue(uuid, e.addrclient);
        if (index == -1)
        {
            OnePacketQueue<DataType> z(p, e);
            this->_QueuThread.add(z);
            Cv.get()->notify_one();
            return true;
        }
        else if (index != 0)
        {
            uuid_copy(p.senderUuid, this->_UuidInThisQueu.at(index - 1).uuid);
            OnePacketQueue<DataType>
                z(p, e);
            this->_QueuThread.add(z);
            Cv.get()->notify_one();
            return true;
        }
        return false;
    }

    /**
     * @brief Force the packet to put it on this queue
     *
     * @param p the packet
     * @param e the socket struct event of the sender
     */
    void PutDataThatQueu(DataType &p, Networks::SocketEvent_u &e)
    {
        OnePacketQueue<DataType> z(p, e);
        this->_QueuThread.add(z);
        Cv.get()->notify_one();
    }

    /**
     * @brief assigne a uuid usr to that queue
     *
     * @param new_uuid new uuid
     * @param addr addrclient struct
     */
    void GenerateNewUuidUsr(uuid_t &new_uuid, const struct sockaddr_in &addr)
    {
        uuid_generate_random(new_uuid);
        char struuid[37] = {};
        uuid_unparse_lower(new_uuid, struuid);

        std::cout << "[Info] New user: " << struuid << std::endl;
        std::cout << "[Info] Add " << struuid << " to " << this->_StrLobbyUuid << std::endl;
        this->_M_mutex.lock();
        this->_UuidInThisQueu.push_back(Uuid(new_uuid, addr));
        this->_M_mutex.unlock();
    }

    /**
     * @brief Check if this queue is empty
     *
     * @return true is empty
     * @return false is not empty
     */
    bool IsQueueEmpty()
    {
        return this->_QueuThread.is_empty();
    }

    /**
     * @brief Get the On Queu object Try to pop the DataType on that queue
     *
     * @param Packet the data to pop
     * @return true a elem was pop
     * @return false nofink was pop
     */
    bool GetOnQueu(OnePacketQueue<DataType> &Packet)
    {
        return this->_QueuThread.try_pop(Packet);
    }

    /**
     * @brief Say if this queue is use by a lobby/game/thread
     *
     * @return true is use
     * @return false is not use
     */
    bool IsUse()
    {
        _M_mutex.lock();
        bool isQueueUse = this->_IsQueuUse;
        _M_mutex.unlock();
        return isQueueUse;
    }

    /**
     * @brief Active the queue for a thread
     *
     */
    void ActivateQueue()
    {
        _M_mutex.lock();
        this->_IsQueuUse = true;
        _M_mutex.unlock();
    }

    /**
     * @brief Remove that user from this queu
     *
     * @param ToRemove
     * @return true
     * @return false
     */
    bool RemouveThatUsrFromThisQueue(const uuid_t &ToRemove)
    {
        size_t pos = 0;
        char StrUsrUuid[37] = {};

        uuid_unparse_lower(ToRemove, StrUsrUuid);
        for (auto &usr : this->_UuidInThisQueu)
        {
            if (uuid_compare(usr.uuid, ToRemove) == 0)
            {
                this->_M_mutex.lock();
                this->_UuidInThisQueu.erase(this->_UuidInThisQueu.begin() + pos);
                this->_M_mutex.unlock();
                std::cout << "[Info] Remove " << StrUsrUuid << " from " << this->_StrLobbyUuid << std::endl;
                return true;
            }
            ++pos;
        }
        std::cout << "[Warning] Imposible to find " << StrUsrUuid << " in " << this->_StrLobbyUuid << std::endl;
        return false;
    }

    /**
     * @brief Add UsrUuid to that queue
     * @brief Do We Have To lock the mutex
     *
     * @param UrsUuid
     * @param addr
     */
    void AddThatUsrToThisQueue(uuid_t &UrsUuid, const struct sockaddr_in &addr, bool Lock)
    {
        char StrUsrUuid[37] = {};
        uuid_unparse_lower(UrsUuid, StrUsrUuid);

        std::cout << "[Info] Add " << StrUsrUuid << " in " << this->_StrLobbyUuid << std::endl;
        if (Lock)
            this->_M_mutex.lock();
        this->_UuidInThisQueu.push_back(Uuid(UrsUuid, addr));
        if (Lock)
            this->_M_mutex.unlock();
    }

    /**
     * @brief Send A packet to One user using OnePacketQueue
     *
     * @param P
     */
    void SendPacketToOneUsr(OnePacketQueue<DataType> &P)
    {
        sendto(P.e.Socket, P.Data, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&P.e.addrclient, sizeof(struct sockaddr_in));
    }

    /**
     * @brief Send A packet to One user
     *
     * @param P
     */
    bool SendPacketByUuid(int SocketServ, uuid_t &SenderUuid, DataType &P)
    {
        for (const auto &C : this->_UuidInThisQueu)
        {
            if (uuid_compare(C.uuid, SenderUuid) == 0)
            {
                sendto(SocketServ, P, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&C.sockaddr, sizeof(struct sockaddr_in));
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Send a New packet to the sender
     *
     * @param P
     * @param ToSend The New packet to send
     */
    void SendPacketToSender(OnePacketQueue<DataType> &P, DataType &ToSend)
    {
        sendto(P.e.Socket, ToSend, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&P.e.addrclient, sizeof(struct sockaddr_in));
    }

    /**
     * @brief Send to all usr in this queue a packet
     *
     * @param ServSocket socket of the server
     * @param P
     */
    void SendPacketToAllUsr(int ServSocket, const DataType &P)
    {
        this->_M_mutex.lock();
        for (auto &usr : this->_UuidInThisQueu)
        {
            sendto(ServSocket, &P, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&usr.sockaddr, sizeof(struct sockaddr_in));
        }
        this->_M_mutex.unlock();
    }

    /**
     * @brief Get the Number Of Usr object
     *
     * @return size_t
     */
    size_t GetNumberOfUsr()
    {
        size_t Nb = 0;
        this->_M_mutex.lock();
        Nb = this->_UuidInThisQueu.size();
        this->_M_mutex.unlock();
        return Nb;
    }

    /**
     * @brief Get the Uuid Of Lobby object
     *
     * @return const uuid_t&
     */
    const uuid_t &GetUuidOfLobby() const
    {
        return this->_UuidOfLobby;
    }

    /**
     * @brief Desactive the queue, the queue can be use by other thread
     *
     */
    void DesactiveQueue()
    {
        this->_M_mutex.lock();
        this->_IsQueuUse = false;
        this->_UuidInThisQueu.clear();
        this->_QueuThread.ClearQueue();
        this->_M_mutex.unlock();
    }

    /**
     * @brief Get the All Usr object
     *
     * @return std::vector<Uuid>&
     */
    std::vector<Uuid> &GetAllUsr()
    {
        return this->_UuidInThisQueu;
    }

    /**
     * @brief Get the Mutex To Lock out of this object
     *
     * @return std::mutex*
     */
    std::mutex *GetMutexToLock()
    {
        return &this->_M_mutex;
    }

    /**
     * @brief Update Uuid of this Queue
     *
     * @param NewUuid
     */
    void UpdateUuidOfQueue(const uuid_t &NewUuid)
    {
        uuid_copy(this->_UuidOfLobby, NewUuid);
    }

    std::mutex MutexCv;
    std::shared_ptr<std::condition_variable> Cv;

private:
    std::vector<Uuid> _UuidInThisQueu;
    utils::SafeQueue<OnePacketQueue<DataType>> _QueuThread;
    std::mutex _M_mutex;
    char _StrLobbyUuid[37] = {};
    uuid_t _UuidOfLobby;
    bool _IsQueuUse = true;
};

/**
 * @brief Data Type
 *
 * @tparam DataType
 */
template <typename DataType>
class HandleUuid
{
public:
    HandleUuid(){};
    ~HandleUuid() = default;

    /**
     * @brief Set the Data On Queu By Usr Uuid object
     *
     * @param p
     * @param uuid
     * @param e
     * @return true
     * @return false
     */
    bool SetDataOnQueuByUsrUuid(DataType &p, const uuid_t &uuid, Networks::SocketEvent_u &e)
    {
        const uuid_t DefaultUsrUuid = {0};

        for (auto &ThreadUuid : this->_QueuByThread)
        {
            if (ThreadUuid.get()->PutDataOnQueueIfUuidThreadIsEgal(p, uuid, e))
                return true;
        }
        if (uuid_compare(uuid, DefaultUsrUuid) == 0)
        {
            this->_QueuByThread.at(0).get()->PutDataThatQueu(p, e);
            return true;
        }
        return false;
    }

    /**
     * @brief Get the Number Active Queue object
     *
     * @return std::size_t
     */
    std::size_t GetNumberActiveQueue()
    {
        std::size_t n = 0;

        this->_Mutex.lock();
        for (const auto &OneThread : this->_QueuByThread)
        {
            if (OneThread.get()->IsUse() == false)
                continue;
            ++n;
        }
        this->_Mutex.unlock();
        return n;
    }

    /**
     * @brief Create a Queu object
     *
     * @param uuid
     * @param index the index of the queue in the tab if the index < nb total queues the queue is re-use
     * @return std::shared_ptr<OneQueu<DataType>>
     */
    std::shared_ptr<OneQueu<DataType>> CreateQueu(uuid_t &uuid, size_t &index)
    {
        std::shared_ptr<OneQueu<DataType>> FistQueuNotUse;

        this->_Mutex.lock();
        for (const auto &queue : this->_QueuByThread)
        {
            if (queue.get()->IsUse() and uuid_compare(uuid, queue.get()->GetUuidOfLobby()) == 0)
            {
                this->_Mutex.unlock();
                throw std::runtime_error("Lobby All Ready Exists");
            }
        }
        if (_GetFistQueuNotUse(FistQueuNotUse, index))
        {
            FistQueuNotUse.get()->ActivateQueue();
            FistQueuNotUse.get()->UpdateUuidOfQueue(uuid);
            this->_Mutex.unlock();
            return FistQueuNotUse;
        }
        std::shared_ptr<OneQueu<DataType>> _NewQueu = std::make_shared<OneQueu<DataType>>(uuid);
        this->_QueuByThread.push_back(_NewQueu);
        this->_Mutex.unlock();
        index = this->_QueuByThread.size() - 1;
        return _NewQueu;
    }

    /**
     * @brief Get the Number Uuid In This Queu object
     *
     * @param LobbyUuid
     * @return int
     * @return -1 Lobby Don't exist
     */
    int GetNumberUuidInThisQueu(const uuid_t &LobbyUuid) const
    {
        for (const auto &ThreadUuid : this->_QueuByThread)
        {
            if (uuid_compare(LobbyUuid, ThreadUuid.get()->GetUuidOfLobby()) == 0)
            {
                return ThreadUuid.get()->GetNumberOfUsr();
            }
        }
        return -1;
    }

    /**
     * @brief Get the uuid of the fist lobby
     *
     * @deprecated use only if we have only one game
     * @param LobbyUuid
     */
    void __GetUuidOfFistLobby(uuid_t &LobbyUuid)
    {
        uuid_copy(LobbyUuid, this->_QueuByThread.at(1).get()->GetUuidOfLobby());
    }

    /**
     * @brief Add This usr to that uuid lobby
     *
     * @param LobbyUuid
     * @param UsrUuid
     * @param addr
     * @param Lock If true the mutex will be locked
     * @return true
     * @return false
     */
    bool AddThisUsrToThatUuidQueuLobby(const uuid_t &LobbyUuid, uuid_t &UsrUuid, const struct sockaddr_in &addr, bool Lock)
    {
        this->_Mutex.lock();
        for (auto &ThreadUuid : this->_QueuByThread)
        {
            if (uuid_compare(LobbyUuid, ThreadUuid.get()->GetUuidOfLobby()) == 0)
            {
                ThreadUuid.get()->AddThatUsrToThisQueue(UsrUuid, addr, Lock);
                this->_Mutex.unlock();
                return true;
            }
        }
        this->_Mutex.unlock();
        return false;
    }

    /**
     * @brief Send packet to all usr on LobbyUuid
     *
     * @param SocketServer
     * @param LobbyUuid
     * @param Packet
     * @return true
     * @return false
     */
    bool SendPacketToAllUserLobby(int SocketServer, const uuid_t &LobbyUuid, DataType &Packet)
    {
        this->_Mutex.lock();
        for (auto &ThreadUuid : this->_QueuByThread)
        {
            if (uuid_compare(LobbyUuid, ThreadUuid.get()->GetUuidOfLobby()) == 0)
            {
                ThreadUuid.get()->SendPacketToAllUsr(SocketServer, Packet);
                this->_Mutex.unlock();
                return true;
            }
        }
        this->_Mutex.unlock();
        return false;
    }

    /**
     * @brief Get the All Urs By Thread object
     *
     * @param LobbyUuid the lobby to find
     * @return std::pair<std::mutex *, std::vector<Uuid> *> the mutex of the lobby and all urs of this lobby
     */
    std::pair<std::mutex *, std::vector<Uuid> *> GetAllUrsByThread(uuid_t &LobbyUuid)
    {
        std::pair<std::mutex *, std::vector<Uuid> *> MutexAndAllUuid;

        this->_Mutex.lock();
        for (auto &ThreadUuid : this->_QueuByThread)
        {
            if (uuid_compare(LobbyUuid, ThreadUuid.get()->GetUuidOfLobby()) == 0)
            {
                MutexAndAllUuid.first = ThreadUuid.get()->GetMutexToLock();
                std::vector<Uuid> &T = ThreadUuid.get()->GetAllUsr();
                MutexAndAllUuid.second = &T;
                this->_Mutex.unlock();
                return MutexAndAllUuid;
            }
        }
        this->_Mutex.unlock();
        return MutexAndAllUuid;
    }

    /**
     * @brief Get the All Uuid Activate Lobby object
     *
     * @return std::vector<std::pair<Uuid, size_t>>  Uuid Of the use lobby and is index
     */
    std::vector<std::pair<Uuid, size_t>> GetAllUuidActivateLobby()
    {
        std::vector<std::pair<Uuid, size_t>> ToRet;
        size_t index = 0;

        for (auto &ThreadUuid : this->_QueuByThread)
        {
            if (index == 0)
            {
                ++index;
                continue;
            }
            if (ThreadUuid.get()->IsUse())
                ToRet.push_back({Uuid(ThreadUuid.get()->GetUuidOfLobby()), index - 1});
            ++index;
        }
        return ToRet;
    }

private:
    /**
     * @brief return OneQueu<DataType> object that is not use
     *
     * @param FistQueuNotUse the fist queue that is not use
     * @param index the index of the queue on the vector object
     * @return true
     * @return false
     */
    bool _GetFistQueuNotUse(std::shared_ptr<OneQueu<DataType>> &FistQueuNotUse, size_t &index)
    {
        for (auto &Queu : this->_QueuByThread)
        {
            if (Queu.get()->IsUse() == false)
            {
                FistQueuNotUse = Queu;
                return true;
            }
            ++index;
        }
        return false;
    }

    std::mutex _Mutex;
    std::vector<std::shared_ptr<OneQueu<DataType>>> _QueuByThread;
};

#endif /* !MANAGEQUEU_HPP_ */
