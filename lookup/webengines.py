import requests
import random
import bs4

headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36'
        }

def ddg_search(query, keywords=None):
    global headers
    results = []
    words = f"{query} {keywords}" if keywords else query
    ddg = f"https://duckduckgo.com/html/?q={words}"
    session = requests.Session()
    data = session.get(ddg, headers=headers)
    soup = bs4.BeautifulSoup(data.text, "html.parser")
    links = soup.select(".result__url")
    titles = soup.select(".result__title")
    for index, link in enumerate(links[:20]):
        result = {"title": titles[index].text, 'url': link.get("href")}
        results.append(result)

    if not results:
        return "No results were found for your search!"
    else:
        results = sorted(results, key=lambda x: random.random())
        final = []
        for index, result in enumerate(results, start=1):
            final.append(f"[****] - Result {index} ({result['title']})\n{result['url']}\n")

        return ''.join(final)

def google_search(query, keywords=None):
    global headers
    results = []
    words = f"{query} {keywords}" if keywords else query
    google = f"https://www.google.com/search?q={words}"
    session = requests.Session()
    data = session.get(google, headers=headers)
    soup = bs4.BeautifulSoup(data.text, "html.parser")
    links = soup.select(".result__url")
    titles = soup.select(".result__title")
    for index, link in enumerate(links[:20]):
        result = {"title": titles[index].text, 'url': link.get("href")}
        results.append(result)

    if not results:
        return "No results were found for your search!"
    else:
        results = sorted(results, key=lambda x: random.random())
        final = []
        for index, result in enumerate(results, start=1):
            final.append(f"[****] - Result {index} ({result['title']})\n{result['url']}\n")

        return ''.join(final)
