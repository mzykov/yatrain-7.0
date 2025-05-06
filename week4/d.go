package main

import (
    "bufio"
    "fmt"
    "strconv"
    "strings"
    "os"
)

func main() {
    scanner := bufio.NewScanner(os.Stdin)
    scanner.Scan()
    n, _ := strconv.Atoi(scanner.Text())

    var v []string

    for i := 0; i < n; i += 1{
        scanner.Scan()
        line := scanner.Text()

        if len(line) == 0 {
            break
        }

        if strings.HasPrefix(line, "Run ") && len(line) > 4 {
            v = append(v, line[4:])
            fmt.Println(v[len(v) - 1])
        } else if strings.HasPrefix(line, "Alt") && len(v) > 0 {
            plus := strings.Count(line, "+") % len(v)

            if plus > 0 {
                prog_idx := len(v) - plus - 1
                prog := v[prog_idx]
                v = append(v[:prog_idx], v[prog_idx + 1:]...)
                v = append(v, prog)
            }

            fmt.Println(v[len(v) - 1])
        } else {
            fmt.Println("")
        }
    }
}
