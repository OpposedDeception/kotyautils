#!/usr/bin/env python3

import argparse
import webengines


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="LookupWeb")
    parser.add_argument("-query", help="A query to search for something", required=True)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--ddg", action="store_true", help="Use DuckDuckGo Engine")
    group.add_argument("--google", action="store_true", help="Use Google Engine")
    parser.add_argument("--keywords", help="Keywords for better search")
    args = parser.parse_args()
    if (args.query and args.keywords and args.ddg) or (args.query and args.ddg):
        res = webengines.ddg_search(query=args.query)
        print(res)
    if (args.query and args.keywords and args.google) or (args.query and args.google):
        result = webengines.google_search(query=args.query)
        print(result)
