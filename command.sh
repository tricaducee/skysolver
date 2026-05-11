#!/usr/bin/env bash
set -euo pipefail

# Usage: ./run_hyperfine.sh args.txt [./sky]
ARGS_FILE=${1:-args.txt}
PROG=${2:-./sky}

if [[ ! -f "$ARGS_FILE" ]]; then
  echo "Args file not found: $ARGS_FILE" >&2
  exit 2
fi

mapfile -t lines < "$ARGS_FILE"

cmds=()
for line in "${lines[@]}"; do
  [[ -z "${line//[[:space:]]/}" ]] && continue   # skip empty/whitespace lines
  cmds+=("$PROG \"$line\"")
done

if [[ ${#cmds[@]} -eq 0 ]]; then
  echo "No arguments found in $ARGS_FILE" >&2
  exit 1
fi

# Print the exact hyperfine invocation (copy/pasteable)
printf 'hyperfine'
for c in "${cmds[@]}"; do
  printf " '%s'" "$c"
done
printf '\n\n'

# Run hyperfine
hyperfine --runs 1 --shell=none "${cmds[@]}" --export-json "6x6.json"
#for c in "${cmds[@]}"; do
#  time "${c}"
#done
