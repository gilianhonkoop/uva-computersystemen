_ = """

Install elixir/erlang:

Ubuntu 14.04/16.04/17.04/18.04/19.04 or Debian 7/8/9/10

  wget https://packages.erlang-solutions.com/erlang-solutions_2.0_all.deb && sudo dpkg -i erlang-solutions_2.0_all.deb
  sudo apt-get update
  sudo apt-get install esl-erlang
  sudo apt-get install elixir


Run it like this (change all four appearences of '16' for different matrix sizes):

make
./test-trans -M 16 -N 16
./csim-ref -v -s 5 -E 1 -b 5 -t trace.f0 > miss.txt
elixir -r parse.exs -e "S.print 16, 16"


Then, the output is in 'parses.txt'

Created by Alfonso Warmerdam, modified by Zirk Seljee

Mac OS: Lines 39 and 40 should be modified to fit the matrices original position.
It's not yet possible to automatically infer the start of each matrix.

"""

defmodule S do
  def writes(flag) do
    File.stream!("miss.txt")
    |> Stream.filter(fn s -> String.starts_with?(s, flag) end)
    |> Stream.drop(1)
    |> Stream.into(File.stream!("miss#{flag}.txt", [:write]))
    |> Stream.run()
  end

  def print(side1, side2) do
    loads = matrix(side1, side2, 0x30A080, "L")
    writes = matrix(side2, side1, 0x34A080, "S")

    File.write!("parses.txt", loads <> "\n\n" <> writes)

    IO.puts("Done!")
  end

  def stringify(data, last_addr, item_count, side1) do
    if (data == []) do
      "\n"
    else
      [[addr, hm] | other_data] = data
      if (addr == last_addr) do
        hm <> stringify(other_data, addr, item_count + 1, side1)
      else
        if (rem(addr, side1) == 0) do 
          "\n"
        else 
          String.duplicate(" ", 3 - item_count) 
        end <> hm <> stringify(other_data, addr, 1, side1)
      end
    end
  end

  def matrix(side1, side2, base, flag) do
    File.stream!("miss.txt")
    |> Stream.filter(fn s -> String.starts_with?(s, flag) end)
    # |> Stream.drop(-2)
    |> Stream.map(fn s ->
      record =
        Regex.run(~r{#{flag} ([0-9a-f]*),4 (hit|miss) (eviction|)}, s, capture: :all_but_first)

      if record == nil do
        [-1, "w"]
      else
        [addr, hm, e] = record

        [
          div(elem(Integer.parse(addr, 16), 0) - base, 4),
          if e == "eviction" do
            "e"
          else
            if String.at(hm, 0) == "h" do
              "·"#"□"
            else
              "m"
            end
          end
        ]
      end
    end)
    |> Stream.filter(fn [addr, _hm] ->
      addr >= 0 and addr < side1 * side2
    end)
    |> Enum.sort()
    |> (&("#{flag} #{side1}x#{side2}:" <> stringify(&1, -1, 0, side1))).()
  end
end
