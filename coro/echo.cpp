
#include <asio.hpp>
#include <asio\experimental\co_spawn.hpp>
using namespace asio::experimental;

awaitable<void> listener()
{
    auto executor = co_await asio::experimental::this_coro::executor();
    auto token = asio::experimental::this_coro::token();
    using namespace asio::ip;
    tcp::acceptor acceptor(executor, { tcp::v4(), 55555 });
    while (true)
    {
        tcp::socket socket = co_await acceptor.async_accept(token);
        char data[1024];
        while (true)
        {
            size_t n = co_await socket.async_read_some(asio::buffer(data), token);
            co_await asio::async_write(socket, asio::buffer(data, n), token);
        }

    }
}

int main()
{
    asio::io_context ioc{ 1 };
    asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&ioc](auto, auto) {ioc.stop(); });
    // TODO
    ioc.run();
    return 0;
}
